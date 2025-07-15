
#include "y/memory/joint/segment.hpp"
#include "y/check/usual.hpp"
#include "y/check/crc32.hpp"
#include "y/format/decimal.hpp"
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

            const char * const Segment:: CallSign     = "Memory::Joint::Segment";
            const size_t       Segment:: SegmentBytes = sizeof(Segment);
            const unsigned     Segment:: SegmentShift = IntegerLog2<SegmentBytes>::Value;
            const size_t       Segment:: MinNumBlocks;
            const size_t       Segment:: MinDataBytes = SegmentBytes + MinNumBlocks * BlockSize;
            const unsigned     Segment:: MinDataShift = CeilLog2(MinDataBytes);
            const unsigned     Segment:: MaxDataShift;

            Segment * Segment:: Format(void * const   entry,
                                       const  unsigned shift)
            {
                //--------------------------------------------------------------
                //
                // sanity check
                //
                //--------------------------------------------------------------
                assert( 0!=entry );
                if(shift<MinDataShift || shift>MaxDataShift)
                    throw Specific::Exception(CallSign,"shift=%s not in %s:%s", Decimal(shift).c_str(), Decimal(MinDataShift).c_str(), Decimal(MaxDataShift).c_str());

                const size_t bytes = size_t(1) << shift;
                assert(bytes>=MinDataBytes);

                const size_t numBlocks = (bytes - SegmentBytes) / BlockSize; assert(numBlocks>=MinNumBlocks);
                assert(numBlocks*BlockSize+SegmentBytes==bytes);

                //--------------------------------------------------------------
                //
                // prepare segment
                //
                //--------------------------------------------------------------
                Segment * const segment = static_cast<Segment *>( Stealth::Zero(entry,bytes) );

                // check
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

                // fill parameters
                segment->param.shift   = shift;
                segment->param.bytes   = bytes;
                segment->param.maxSize = segment->head->size;
                assert(IsValid(segment));

                return segment;
            }


            void Segment:: display(std::ostream &os) const
            {
                assert(IsValid(this));

                size_t numUsed = 0;
                os << '[';
                for(const Block *block=head;block!=tail;block=block->next)
                {
                    if(block->used)
                    {
                        assert(this==block->used);
                        // used
                        os << '*';
                        ++numUsed;
                    }
                    else
                    {
                        os << '#';
                    }
                    os << block->size;
                }
                os << ']' << " / " << numUsed << std::endl;
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
                    Y_Segment_Check(Aligned(block->size)==block->size);
                }
                return true;
            }



            void * Segment:: acquire(size_t & request) noexcept
            {
                assert(IsValid(this));

                //--------------------------------------------------------------
                //
                // check possibility
                //
                //--------------------------------------------------------------
                if(request>param.maxSize) return 0;

                //--------------------------------------------------------------
                //
                // loop over free blocks
                //
                //--------------------------------------------------------------
                const Block * const end = tail;
                for(Block *block=head;block!=end;block=block->next)
                {

                    //----------------------------------------------------------
                    // check if block is used
                    //----------------------------------------------------------
                    if(block->used) {
                        assert(this==block->used);
                        continue; // used blocks
                    }

                    //----------------------------------------------------------
                    // check if block can accept request
                    //----------------------------------------------------------
                    if(block->size<request)
                        continue; // block is too small

                    //----------------------------------------------------------
                    // using alignment
                    //----------------------------------------------------------
                    {
                        const size_t aligned = Aligned( Max(request,BlockSize) ); assert(aligned<=block->size);
                        const size_t remains = block->size - aligned; assert(0==remains%BlockSize);
                        if(remains>=2*BlockSize)
                        {
                            // split
                            const size_t requestedBlocks = aligned>>BlockLog2;
                            const size_t remainingBlocks = remains>>BlockLog2;
                            Block * const nxt = block->next;
                            Block * const cut = block+1+requestedBlocks;
                            cut->used   = 0;
                            cut->next   = nxt;
                            cut->prev   = block;
                            cut->size   = (remainingBlocks-1) << BlockLog2;
                            nxt->prev   = cut;
                            block->next = cut;
                            block->size = aligned;
                            assert(IsValid(this));
                        }
                    }

                    //----------------------------------------------------------
                    // update and return
                    //----------------------------------------------------------
                    block->used = this;
                    assert(IsValid(this));
                    return memset(block+1,0,request = block->size);
                }

                //--------------------------------------------------------------
                //
                // not found, leave request untouched
                //
                //--------------------------------------------------------------
                return 0;
            }


            uint32_t Segment:: crc32(uint32_t crc) const noexcept
            {
                assert(IsValid(this));
                for(const Block *block=head;block;block=block->next)
                {
                    crc = CRC32::Run(crc, block, sizeof(Block));
                }
                return crc;
            }

            bool Segment:: owns(const void * const addr) const noexcept
            {
                assert(0!=addr);
                assert( IsValid(this) );
                return addr >= (const void *)(head+1) && addr < (const void *)(tail);
            }

            bool Segment:: owns(const void * blockAddr, size_t &blockSize) const noexcept
            {
                assert(0!=blockAddr);
                for(const Block *block = head; block != tail; block=block->next)
                {
                    if(block+1==blockAddr)
                    {
                        blockSize = block->size;
                        return true;
                    }
                }
                return false;
            }

            bool Segment:: isEmpty() const noexcept
            {
                assert(IsValid(this));
                return (!head->used) && (tail == head->next);
            }


            Segment::Block * Segment:: GetBlockOf(const void * const addr) noexcept
            {
                assert(0!=addr);
                const Block *   const block   = static_cast<const Block *>(addr)-1;
                assert(0!=block);
                assert(block->used);
                return (Block *)block;
            }



            Segment * Segment:: Release(void *const blockAddr, const size_t blockSize) noexcept
            {
                // get block from address
                assert(0!=blockAddr);
                
                Block *   const block   = GetBlockOf(blockAddr); assert(0!=block);
                Segment * const segment = block->used;

                assert(0!=segment);
                assert(segment->owns(blockAddr));
                assert(IsValid(segment));

                if(blockSize>block->size)
                    Libc::Error::Critical(EINVAL,
                                          "%s::Release(blockSize=%s>block->size=%s)",
                                          CallSign,
                                          Decimal(blockSize  ).c_str(),
                                          Decimal(block->size).c_str());

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

                assert(IsValid(segment));
                return segment;
            }

            const size_t Segment:: Reserved   = SegmentBytes+2*BlockSize;
            const size_t Segment:: MaxRequest = MaxDataBytes - Reserved;

            unsigned  Segment:: ShiftFor(const size_t request)
            {
                if(request>MaxRequest) throw Specific::Exception(CallSign,"request=%s>%s",Decimal(request).c_str(),Decimal(MaxRequest).c_str());
                const size_t raw   = SegmentBytes + 2*BlockSize + request;
                unsigned     shift = 0;
                (void) NextPowerOfTwo( Max(raw,MinDataBytes), shift);
                assert(shift>=MinDataShift);
                assert(shift<=MaxDataShift);
                return shift;
            }

            size_t Segment:: MaxSizeFor(const unsigned shift)
            {
                assert(shift>=MinDataShift);
                assert(shift<=MaxDataShift);
                return (size_t(1) << shift) - Reserved;
            }



            size_t Segment::  Aligned(const size_t request)
            {
                // TODO: check with MaxRequest...
                static const size_t MaxAlignedRequest = Aligning::Maximum;
                if(request>MaxAlignedRequest)
                {
                    throw Specific::Exception(CallSign,"request=%s exceeds %s", Decimal(request).c_str(), Decimal(MaxAlignedRequest).c_str());
                }
                return Aligning::Ceil(request);
            }

        }
    }

}

