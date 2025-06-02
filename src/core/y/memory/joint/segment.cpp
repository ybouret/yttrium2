
#include "y/memory/joint/segment.hpp"
#include "y/check/usual.hpp"
#include "y/check/crc32.hpp"
#include "y/decimal.hpp"
#include "y/system/exception.hpp"
#include "y/memory/stealth.hpp"
#include "y/memory/sentinel.hpp"
#include "y/core/utils.hpp"

#include <iostream>
#include <cstring>

namespace Yttrium
{
    namespace Memory
    {
        namespace Joint
        {

            const char * const Segment:: CallSign = "Memory::Joint::Segment";
            const size_t       Segment:: SegmentBytes = sizeof(Segment);
            const size_t       Segment:: MinNumBlocks;
            const size_t       Segment:: MinDataBytes = SegmentBytes + MinNumBlocks * BlockSize;
            const size_t       Segment:: MaxDataBytes;

            Segment * Segment:: Format(void * const  entry,
                                       const  size_t bytes)
            {
                // sanity check
                assert( Good(entry,bytes) );
                if(bytes<MinDataBytes||bytes>MaxDataBytes)
                    throw Specific::Exception(CallSign,"bytes=%s not in %s:%s", Decimal(bytes).c_str(), Decimal(MinDataBytes).c_str(), Decimal(MaxDataBytes).c_str());

                assert(0!=entry);
                assert(bytes>=MinDataBytes);
                assert(bytes<=MaxDataBytes);

                const size_t numBlocks = (bytes - SegmentBytes) / BlockSize; assert(numBlocks>=MinNumBlocks);
                if(numBlocks*BlockSize+SegmentBytes!=bytes)
                    throw Specific::Exception(CallSign,"unaligned bytes=%s", Decimal(bytes).c_str());;

                // prepare segment
                Segment * const segment = static_cast<Segment *>( Stealth::Zero(entry,bytes) );

                // check and perform various links
                assert(0!=segment);
                assert(0==segment->next);
                assert(0==segment->prev);

                // prepare head and tail
                Coerce(segment->head) = static_cast<Block *>(Stealth::Incr(entry, SegmentBytes));
                Coerce(segment->tail) = segment->head + (numBlocks-1);
                assert(!segment->head->used);
                assert(!segment->tail->used);

                segment->head->next = segment->tail;
                segment->tail->prev = segment->head;
                segment->head->size = (numBlocks-2) << BlockLog2;
                segment->tail->used = segment;

                // parameters
                segment->param.bytes           = bytes;
                segment->param.nextPowerOfTwo  = NextPowerOfTwo(segment->param.bytes, segment->param.shift);
                segment->param.isDyadic        = ( segment->param.bytes ==  segment->param.nextPowerOfTwo );
                assert(IsValid(segment));

                return segment;
            }


            void Segment:: Display(const Segment * const segment, std::ostream &os)
            {
                assert(0!=segment);
#if !defined(NDEBUG)
                volatile Sentinel sentinel1(*segment);
                volatile Sentinel sentinel2(*segment->head);
                volatile Sentinel sentinel3(*segment->tail);
#endif

                os << '[';
                for(const Block *block=segment->head;block!=segment->tail;block=block->next)
                {
                    if(block->used)
                    {
                        assert(segment==block->used);
                        // used
                        os << '*';
                    }
                    else
                    {
                        os << '#';
                    }
                    os << block->size;
                }
                os << ']' << std::endl;
            }

#define Y_Segment_Check(EXPR) do {\
if(!(EXPR)) { std::cerr << "\t*** " << #EXPR << std::endl; return false; } \
} while(false)

            bool Segment:: IsValid(const Segment * const segment) noexcept
            {
                Y_Segment_Check(0!=segment);
                Y_Segment_Check(0!=segment->head);
                Y_Segment_Check(0!=segment->tail);
                Y_Segment_Check(segment==segment->tail->used);
                Y_Segment_Check(0==segment->tail->size);

                for(const Block *block=segment->head;block!=segment->tail;block=block->next)
                {
                    if(block->used) Y_Segment_Check(segment==block->used);
                    const Block * const next = block->next;
                    Y_Segment_Check(0!=next);
                    Y_Segment_Check(block==next->prev);
                    const size_t numBlocks = static_cast<size_t>(next-block);
                    Y_Segment_Check(numBlocks>=2);
                    const size_t numBytes  = (numBlocks-1)*BlockSize;
                    Y_Segment_Check(numBytes==block->size);
                }
                return true;
            }



            void * Segment:: Acquire(Segment * const segment,
                                     size_t &        request) noexcept
            {
                assert(IsValid(segment));

                for(Block *block=segment->head;block!=segment->tail;block=block->next)
                {

                    // check if block is used
                    if(block->used) {
                        assert(segment==block->used);
                        continue; // used blocks
                    }

                    // check if block can accept request
                    if(block->size<request)
                        continue; // block is too small

                    // using alignment
                    const size_t aligned = Alignment::To<Block>::Ceil( MaxOf(request,BlockSize) );
                    assert(aligned<=block->size);
                    {
                        const size_t remains = block->size - aligned; assert(0==remains%BlockSize);
                        if(remains>=2*BlockSize)
                        {
                            // split
                            const size_t requestedBlocks = aligned>>BlockLog2;
                            const size_t remainingBlocks = remains>>BlockLog2;
                            Block * const next = block->next;
                            Block * const slit = block+1+requestedBlocks;
                            slit->used  = 0;
                            slit->next  = next;
                            slit->prev  = block;
                            slit->size  = (remainingBlocks-1) << BlockLog2;
                            next->prev  = slit;
                            block->next = slit;
                            block->size = aligned;
                            assert(IsValid(segment));
                        }
                    }

                    block->used = segment;
                    assert(IsValid(segment));
                    return memset(block+1,0,request = block->size);
                }

                // not found, leave request untouched
                return 0;
            }


            uint32_t Segment:: CRC(const Segment * segment) noexcept
            {
                assert(IsValid(segment));
                uint32_t crc = 0;
                for(const Block *block=segment->head;block;block=block->next)
                {
                    CRC32::Run(crc, block, sizeof(Block));
                }
                return crc;
            }

            bool Segment:: Owns(const Segment * const segment, void * const addr) noexcept
            {
                assert(0!=addr);
                assert( IsValid(segment) );
                return addr >= (const void *)(segment->head+1) && addr < (const void *)(segment->tail);
            }

            bool Segment:: IsEmpy(const Segment *const segment) noexcept
            {
                assert(IsValid(segment));
                Block * const head = segment->head;
                return !head->used && segment->tail == head->next;
            }


            Segment * Segment:: Release(void *const addr) noexcept
            {
                // get block from address
                assert(0!=addr);
                Block *   const block   = static_cast<Block *>(addr)-1;
                Segment * const segment = block->used;

                assert(block->used);
                assert(Owns(segment,addr));

                // check situation
                static const unsigned MERGE_NONE = 0x00;
                static const unsigned MERGE_PREV = 0x01;
                static const unsigned MERGE_NEXT = 0x02;
                static const unsigned MERGE_BOTH = MERGE_PREV | MERGE_NEXT;

                unsigned      flags = MERGE_NONE;
                Block * const prev  = block->prev;
                Block * const next  = block->next; assert(0!=next);
                if(prev && !prev->used) { flags |= MERGE_PREV; assert(segment->head!=block); }
                if(!next->used)         { flags |= MERGE_NEXT; assert(segment->tail!=block); }

                switch(flags)
                {
                    case MERGE_PREV: {
                        //std::cerr << "should merge prev" << std::endl;
                        prev->next = next;
                        next->prev = prev;
                        prev->size = (static_cast<size_t>(next-prev)-1) << BlockLog2;
                        assert(IsValid(segment) || Die("MERGE_PREV") );
                    } break;

                    case MERGE_NEXT: {
                        //std::cerr << "should merge next" << std::endl;
                        Block * const after = next->next; assert(0!=after);
                        block->next = after;
                        after->prev = block;
                        block->size = (static_cast<size_t>(after-block)-1) << BlockLog2;
                        block->used = 0;
                        assert(IsValid(segment) || Die("MERGE_NEXT") );
                    } break;

                    case MERGE_BOTH: {
                        //std::cerr << "should merge both" << std::endl;
                        Block * const after = next->next; assert(0!=after);
                        prev->next  = after;
                        after->prev = prev;
                        prev->size = (static_cast<size_t>(after-prev)-1) << BlockLog2;
                        assert(IsValid(segment) || Die("MERGE_BOTH") );
                    } break;

                    default:
                        assert(MERGE_NONE==flags);
                        block->used = 0;
                        assert(IsValid(segment) || Die("MERGE_NONE") );
                        break;
                }


                return segment;
            }

            size_t Segment:: BytesFor(const size_t blockSize)
            {
                
            }



        }
    }

}

