
#include "y/ability/collectable.hpp"
#include "y/hexadecimal.hpp"
#include <iostream>

namespace Yttrium
{
    Collectable:: ~Collectable() noexcept
    {
    }

    Collectable:: Collectable() noexcept
    {
    }

    //! w[1..n] = u[1..n]/0xff
    static inline
    void shortDivision(uint8_t        w[],
                       const uint8_t  u[],
                       const unsigned n) noexcept
    //Short division: the unsigned radix 256 integer u[1..n] is divided by the integer iv (in the
    //                               range 0 ≤ iv ≤ 255), yielding a quotient w[1..n] and a remainder ir (with 0 ≤ ir ≤ 255).
    {
        const int iv = 0xff;
        int       ir = 0;
        for(unsigned j=1;j<=n;j++) {
            const int i=256*ir+u[j];
            w[j]=uint8_t(i/iv);
            ir=i % iv;
        }
    }

    size_t Collectable:: Mul(const uint8_t amountOf, const size_t total) noexcept
    {

        static const unsigned width = sizeof(size_t);
        static const unsigned n     = width+1;

        // total * amountOf / 0xff
        uint8_t prod[n];


        {
            const uint16_t factor = amountOf;
            uint16_t       carry = 0;
            for(size_t i=0;i<sizeof(size_t);++i)
            {
                uint16_t b = (total>> (i*8)) & 0xff;
                std::cerr << "using b=" << b << std::endl;
                carry += (b*factor);
                prod[i] = uint8_t(carry);
                carry >>= 8;
            }
            prod[sizeof(size_t)] = uint8_t(carry);

            std::cerr << "prod=0x";
            for(int i=width;i>=0;--i)
            {
                std::cerr<< Hexadecimal::LowerByte[prod[i]];
            }
            std::cerr << std::endl;
        }

        // divide by 0xff
        uint8_t quot[n];
        shortDivision(quot-1,prod-1,n);
        std::cerr << "quot=0x";
        for(int i=width;i>=0;--i)
        {
            std::cerr<< Hexadecimal::LowerByte[quot[i]];
        }
        std::cerr << std::endl;



        return 0;
    }
}
