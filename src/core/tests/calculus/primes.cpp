
#include "y/calculus/prime/next.hpp"
#include "y/utest/run.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/stream/libc/output.hpp"
#include "y/calculus/bits-for.hpp"
#include "y/format/hexadecimal.hpp"

using namespace Yttrium;

template <typename T> static inline
T Transform(const T &x)
{
    return x;
}

Y_UTEST(calculus_primes)
{

    uint32_t i    = 3;
    uint32_t n    = 0;
    uint32_t dmax = 0;

    while(true)
    {
        const uint32_t j = Prime::Next(i+1);
        ++n;
        //const uint32_t k = (i-1)>>1;
        const uint32_t d = (j-i); Y_ASSERT( 0 == (d&1) );
        const uint32_t delta = (d>>1) -1;
        const unsigned dbits = BitsFor(delta);
        if(dbits>8) break;
        if(delta>dmax)
            dmax = delta;
        std::cerr << Hexadecimal(j) << " -> d/2-1 = " << std::setw(3) << delta << " #bits = " << std::setw(2) << dbits << " #" << std::setw(10) << n << " | " << j << std::endl;
        if(n>=65536) break;


        i=j;

    }




}
Y_UDONE()

