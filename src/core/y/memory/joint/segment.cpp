
#include "y/memory/joint/segment.hpp"
#include "y/check/usual.hpp"
#include "y/decimal.hpp"
#include "y/system/exception.hpp"
#include "y/memory/stealth.hpp"
#include "y/memory/sentinel.hpp"
#include "y/core/utils.hpp"

#include <iostream>

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

            Segment * Segment:: Format(void * const  entry,
                                       const  size_t bytes)
            {
                // sanoty check
                assert( Good(entry,bytes) );
                if(bytes<MinDataBytes)
                    throw Specific::Exception(CallSign,"bytes=%s<MinDataBytes=%s", Decimal(bytes).c_str(), Decimal(MinDataBytes).c_str());
                assert(0!=entry);
                assert(bytes>=MinDataBytes);

                const size_t numBlocks = (bytes - SegmentBytes) / BlockSize; assert(numBlocks>=MinNumBlocks);
                std::cerr << "numBlocks=" << numBlocks << " in " << bytes << " bytes " << std::endl;
                Segment * const segment = static_cast<Segment *>( Stealth::Zero(entry,bytes) );

                // check and perform various links
                assert(0!=segment);
                assert(0==segment->next);
                assert(0==segment->prev);

                Coerce(segment->head) = static_cast<Block *>(Stealth::Incr(entry, SegmentBytes));
                Coerce(segment->tail) = segment->head + (numBlocks-1);
                assert(!segment->head->used);
                assert(!segment->tail->used);

                segment->head->next   = segment->tail;
                segment->tail->prev   = segment->head;
                segment->head->size   = sizeof(Block) * (numBlocks-2);

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


            void * Segment:: Acquire(Segment * const segment,
                                     size_t &        blockSize) noexcept
            {
                assert(0!=segment);
                for(Block *block=segment->head;block!=segment->tail;block=block->next)
                {
                    if(block->used) {
                        assert(segment==block->used);
                        continue; // used blocks
                    }

                    assert(block->size>=sizeof(Block));

                    if(block->size<blockSize)
                        continue; // block is too small

                    const size_t required = Alignment::To<Block>::Ceil( MaxOf(blockSize,BlockSize) );


                    std::cerr << "blockSize = " << blockSize << " -> " << required << std::endl;;
                    {
                        const size_t remaining = block->size - required;
                        std::cerr << "remaining=" << remaining << std::endl;
                        if(remaining>=2*BlockSize)
                            std::cerr << "should split" << std::endl;
                    }

                    block->used = segment;
                    blockSize   = block->size;
                    return block+1;
                }

                // not found, leave blockSize untouched
                return 0;
            }

        }
    }

}

