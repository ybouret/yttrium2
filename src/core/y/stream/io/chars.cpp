
#include "y/stream/io/chars.hpp"

namespace Yttrium
{
    namespace IO
    {
        Chars:: Chars() : CharsProto( Char::CacheInstance() )
        {
        }

        Chars:: ~Chars() noexcept
        {
        }

        Chars:: Chars(const Chars &other) : CharsProto( other.pool ), Recyclable()
        {
            duplicate(other);
        }

        Chars & Chars:: operator=(const Chars &other)
        {
            Chars temp(other);
            list.swapListFor(temp.list);
            return *this;
        }

        void Chars:: free() noexcept { freeList_(); }
    }

}

