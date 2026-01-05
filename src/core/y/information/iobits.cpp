

#include "y/information/iobits.hpp"

namespace Yttrium
{
    namespace Information
    {
        IOBits:: IOBits() : IOBitsProto( IOBit::CacheInstance() )
        {
        }

        IOBits:: ~IOBits() noexcept
        {
        }

        IOBits:: IOBits(const IOBits &other) : IOBitsProto( other.pool ), Recyclable()
        {
            duplicate(other);
        }

        IOBits & IOBits:: operator=(const IOBits &other)
        {
            IOBits temp(other);
            list.swapListFor(temp.list);
            return *this;
        }

        void IOBits:: free() noexcept { freeList_(); }
    }

}

