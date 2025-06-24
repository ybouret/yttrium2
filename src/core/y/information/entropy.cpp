#include "y/information/entropy.hpp"
#include "y/check/usual.hpp"
#include <cstring>
#include <cmath>

namespace Yttrium
{

    namespace Information
    {

        void Entropy:: ldz() noexcept
        {
            memset(bin,0,sizeof(bin));
        }

        Entropy:: Entropy() noexcept : bin()
        {
            ldz();
        }

        Entropy:: ~Entropy() noexcept
        {

        }

        Entropy:: Entropy(const Entropy &other) noexcept : bin()
        {
            memcpy(bin,other.bin,sizeof(bin));
        }

        void Entropy:: write(const char C)
        {
            ++bin[ uint8_t(C) ];
        }

        void Entropy:: flush()
        {
        }

        void Entropy:: frame(const void *const entry, const size_t count)
        {
            assert( Good(entry,count) );
            const uint8_t *p = (const uint8_t *)entry;
            for(size_t i=count;i>0;--i)
                ++bin[ *(p++) ];
        }

        long double Entropy:: operator()(void) const
        {
            uint64_t sum = 0;
            for(size_t i=0;i<256;++i) sum += bin[i];
            if(sum<=0) return 0;

            long double res = 0;
            for(size_t i=0;i<256;++i)
            {
                const uint64_t n = bin[i];
                if(n>0)
                {
                    const long double p = ((long double)n) / sum;
                    res -= p * std::log(p);
                }
            }
            return res;
        }


    }

}
