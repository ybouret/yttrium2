

#include "y/stream/io/bits.hpp"
#include "y/calculus/alignment.hpp"

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

        Bits & Bits:: to(Bits &reservoir) noexcept
        {
            volatile Lock _(*this), __(reservoir);
            reservoir->mergeTail( **this );
            return *this;
        }

        Bits & Bits:: skip(size_t nbit, Bits &reservoir) noexcept
        {
            volatile Lock _(*this), __(reservoir);
            assert(list.size>=nbit);
            while(nbit-- > 0) reservoir->pushTail( list.popHead() );
            return *this;
        }

        size_t Bits:: write(OutputStream &fp, Bits &reservoir)
        {
            size_t count = 0;
            while(list.size>=8)
            {
                fp.write( (char) pop<uint8_t>(reservoir) );
                ++count;
            }
            return count;
        }

        size_t Bits:: flush(OutputStream &output, Bits &reservoir)
        {
            volatile Lock _(*this), __(reservoir);
            size_t pad  = Alignment::On<8>::Ceil(list.size) - list.size;
            while(pad-- > 0)
                list.pushTail( reservoir.query(false) );
            return write(output,reservoir);
        }




    }

}

