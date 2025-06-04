
#include "y/ability/collectable.hpp"
#include "y/hexadecimal.hpp"
#include "y/container/algorithm/reverse.hpp"

#include <iostream>

namespace Yttrium
{
    Collectable:: ~Collectable() noexcept
    {
    }

    Collectable:: Collectable() noexcept
    {
    }

    //! w[0..n-1] = u[0..n-1]/0xff
    static inline
    void shortDivision(uint8_t        * w,
                       const uint8_t  * u) noexcept
    {
        static const unsigned n     = sizeof(size_t) + 1;
        static const int      denom = 0xff;

        --u;
        --w;
        int       ir = 0;
        for(unsigned j=1;j<=n;j++) {
            const int i=256*ir+u[j];
            w[j]=uint8_t(i/denom);
            ir=i % denom;
        }
    }

    size_t Collectable:: Portion(const uint8_t amount, const size_t total) noexcept
    {

        static const unsigned width = sizeof(size_t);
        static const unsigned n     = width+1;

#if defined(NDEBUG)
        switch(amount)
        {
            case 0:    return 0;
            case 0xff: return total;
            default:
                break;
        }
#endif
        
        // short product
        uint8_t prod[n];
        {
            const uint16_t factor = amount;
            uint16_t       carry = 0;
            for(size_t i=0;i<sizeof(size_t);++i)
            {
                uint16_t b = (total>> (i*8)) & 0xff;
                carry += (b*factor);
                prod[i] = uint8_t(carry);
                carry >>= 8;
            }
            prod[sizeof(size_t)] = uint8_t(carry);
            Algorithm::Reverse(prod,n,Swap<uint8_t>);
        }

        // short division
        uint8_t quot[n];
        shortDivision(quot,prod);
        assert(0x00==quot[0]);

        // assemble answer
        size_t ans = 0;
        for(unsigned i=1;i<n;++i)
        {
            ans <<= 8;
            ans |= quot[i];
        }

        return ans;
    }


    void Collectable:: release() noexcept
    {
        gc(All);
    }

    size_t Collectable:: NewSize(const uint8_t amount, const size_t oldSize) noexcept
    {
        return oldSize - Portion(amount,oldSize);
    }


}
