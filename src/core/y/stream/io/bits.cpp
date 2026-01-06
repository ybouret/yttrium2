

#include "y/stream/io/bits.hpp"

namespace Yttrium
{
    namespace IO
    {
        Bits:: Bits() : BitsProto( Bit::CacheInstance() )
        {
        }

        Bits:: ~Bits() noexcept
        {
        }

        Bits:: Bits(const Bits &other) : BitsProto( other.pool ), Recyclable()
        {
            duplicate(other);
        }

        Bits & Bits:: operator=(const Bits &other)
        {
            Bits temp(other);
            list.swapListFor(temp.list);
            return *this;
        }

        void Bits:: free() noexcept { freeList_(); }

        std::ostream & operator<<(std::ostream &os, const Bits &bits)
        {
            os << '[';
            for(const Bit *b=bits->head;b;b=b->next)
            {
                os << ( (**b) ? '1' : '0' );
            }
            return os << ']';
        }

        void Bits:: to(Bits &pool) noexcept
        {
            pool->mergeTail( **this );
        }


    }

}

