
#include "y/jive/pattern/first-chars.hpp"
#include "y/ascii/printable.hpp"
#include "y/calculus/bits-in.hpp"
#include <iostream>
#include <cstring>
#include <cassert>

namespace Yttrium
{
    namespace Jive
    {
        FirstChars:: FirstChars() noexcept :
        size(0),
        data()
        {
            free();
            assert(0==Calculus::BitsIn::Block(data,sizeof(data)));
        }


        void FirstChars:: free() noexcept
        {
            memset(data,0,sizeof(data));
            Coerce(size) = 0;
        }

        void FirstChars:: all() noexcept
        {
            memset(data,0xff,sizeof(data));
            Coerce(size) = 256;
        }


        FirstChars:: FirstChars(const FirstChars &fc) noexcept :
        size(fc.size),
        data()
        {
            memcpy(data,fc.data,sizeof(data));
        }

        FirstChars & FirstChars:: operator=(const FirstChars &fc) noexcept
        {
            Coerce(size) = fc.size;
            memmove(data,fc.data, sizeof(data) );
            return *this;
        }


        static const uint8_t fcbit[8] = {1,2,4,8,16,32,64,128};

        bool FirstChars:: getbit(const uint8_t b) const noexcept
        {
            return 0 != (data[b>>3] & fcbit[b&7]);
        }

        void FirstChars:: setbit(const uint8_t b) noexcept
        {
            (data[b>>3] |= fcbit[b&7]);
        }

        static const uint8_t fcmsk[8] = {255-1,255-2,255-4,255-8,255-16,255-32,255-64,255-128};


        void FirstChars:: clrbit(const uint8_t b) noexcept
        {
            data[b>>3] &= fcmsk[b&7];
        }

        std::ostream & operator<<(std::ostream &os, const FirstChars &fc)
        {
            os << '[';
            for(unsigned i=0;i<256;++i)
            {
                if(fc.getbit(i)) os << ASCII::Printable::Char[i];
            }
            os << ']';
            return os;
        }

    }

}

