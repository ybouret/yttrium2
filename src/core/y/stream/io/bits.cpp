

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

        Bits & Bits:: to(Bits &pool) noexcept
        {
            pool->mergeTail( **this );
            return *this;
        }

        Bits & Bits:: skip(size_t nbit, Bits &pool) noexcept
        {
            assert(list.size>=nbit);
            while(nbit-- > 0) pool->pushTail( list.popHead() );
            return *this;
        }

        Bits & Bits:: send(OutputStream &fp, Bits &pool)
        {
            while(list.size>=8)
                fp.write( (char) pop<uint8_t>(pool) );
            

            return *this;
        }



    }

}

