
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

    Vector<uint8_t> gap;
    while(true)
    {
        const uint32_t j   = Prime::Next(i+1);
        const uint32_t g   = j-i;    Y_ASSERT( 0 == (g&1)  );
        const uint32_t d   = (g>>1); Y_ASSERT(d<256);
        gap << d;
        i = j;
        if( j >= IntegerFor<uint16_t>::Maximum )
            break;
    }
    std::cerr << "#gap=" << gap.size() << std::endl;

    i = 3; Y_ASSERT(Prime::Test(i));
    for(size_t k=1;k<=gap.size();++k)
    {
        i += gap[k] << 1; std::cerr << i << std::endl;
        Y_ASSERT(Prime::Test(i));
    }


#if 0
    uint32_t dmax = 0;

    while(true)
    {
        const uint32_t j = Prime::Next(i+1);
        const uint32_t d = (j-i); Y_ASSERT( 0 == (d&1) );
        const uint32_t delta = (d>>1) -1;
        const unsigned dbits = BitsFor(delta);
        if(dbits>8) break;
        if(delta>dmax)
            dmax = delta;
        std::cerr << Hexadecimal(j) << " -> d/2-1 = " << std::setw(3) << delta << " #bits = " << std::setw(2) << dbits << " #" << std::setw(10) << n << " | " << j << std::endl;
        if(j>=65536) break;

        ++n;
        if(n>=65536) break;

        i=j;

    }
#endif




}
Y_UDONE()

