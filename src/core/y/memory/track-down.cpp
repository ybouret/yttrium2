
#include "y/memory/track-down.hpp"

#include "y/memory/small/blocks.hpp"
#include "y/memory/allocator/pooled.hpp"

#include <iostream>
#include <iomanip>

namespace Yttrium
{
    namespace Memory
    {


        Variety TrackDown:: Which(const void * const blockAddr,
                                  size_t &           blockSize)
        {
            assert(0!=blockAddr);
            blockSize = 0;

            if( Small::Blocks::Instance().owns(blockAddr,blockSize))
                return SmallType;

            if( Pooled::Instance().owns(blockAddr,blockSize) )
                return JointType;

            return OtherType;
        }

        std::ostream & TrackDown:: Print(std::ostream &os, const void * const blockAddr)
        {
            size_t        blockSize = 0;
            const Variety variety   = Which(blockAddr,blockSize);

            switch(variety)
            {
                case SmallType: os << "Small@" << blockAddr << "[" << blockSize << "]"; break;
                case JointType: os << "Joint@" << blockAddr << "[" << blockSize << "]"; break;
                case OtherType: os << "Other@" << blockAddr; break;
            }
            return os;
        }
    }

}
