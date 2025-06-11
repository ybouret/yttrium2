
#include "y/memory/track-down.hpp"

#include "y/memory/small/blocks.hpp"
#include "y/memory/allocator/pooled.hpp"

namespace Yttrium
{
    namespace Memory
    {


        Variety TrackDown(const void * const blockAddr,
                          size_t & blockSize) noexcept
        {
            assert(0!=blockAddr);
            blockSize = 0;

            if( Small::Blocks::Instance().owns(blockAddr,blockSize))
                return SmallType;

            if( Pooled::Instance().owns(blockAddr,blockSize) )
                return JointType;
            
            return OtherType;
        }
    }

}
