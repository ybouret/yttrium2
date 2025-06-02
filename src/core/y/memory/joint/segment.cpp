
#include "y/memory/joint/segment.hpp"
#include "y/check/usual.hpp"
#include "y/decimal.hpp"
#include "y/system/exception.hpp"
#include "y/memory/stealth.hpp"

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
                segment->head->next = segment->tail;
                segment->tail->prev = segment->head;
                segment->head->size = sizeof(Block) * (numBlocks-2);

                return segment;
            }


            void Segment:: Display(const Segment * const segment, std::ostream &os)
            {
                os << '[';
                for(const Block *block=segment->head;block->next!=segment->tail;block=block->next)
                {
                    
                }
                os << ']' << std::endl;
            }
        }

    }

}

