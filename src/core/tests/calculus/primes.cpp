
#include "y/calculus/prime/next.hpp"
#include "y/utest/run.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/stream/libc/output.hpp"
#include "y/calculus/bits-for.hpp"

using namespace Yttrium;

template <typename T> static inline
T Transform(const T &x)
{
    return x;
}

Y_UTEST(calculus_primes)
{

    uint32_t i = 3;
    uint32_t n = 0;
    while(true)
    {
        const uint32_t j = Prime::Next(i+1);
        ++n;
        //const uint32_t k = (i-1)>>1;
        const uint32_t d = (j-i); Y_ASSERT( 0 == (d&1) );
        const uint32_t delta = (d>>1) -1;
        const unsigned dbits = BitsFor(delta);
        std::cerr << j << " -> d/2-1 = " << delta << " #bits = " << dbits << " #" << n << std::endl;
        //if(n>=65536) break;

        i=j;

        if(dbits>8) break;
    }



#if 0
    {
        Vector<unsigned> p8;
        // precomputing
        for(unsigned i=0;i<256;++i)
        {
            if( Prime::Test(i) ) p8 << i;
        }

        std::cerr << "#8=" << p8.size() << std::endl;

        OutputFile fp("prime8.hxx");
        for(size_t i=1;i<=p8.size();++i)
        {
            fp("\t0x%02x /* %2u */", p8[i], unsigned(i));
            if(i<p8.size()) fp << ',';
            fp << '\n';
        }
    }

    {
        Vector<uint32_t> p16;
        for(uint32_t i=256;i<65536;++i)
        {
            if( Prime::Test(i) ) p16 << i;
        }
        std::cerr << "#16=" << p16.size() << std::endl;
        OutputFile fp("prime16.hxx");
        for(size_t i=1;i<=p16.size();++i)
        {
            fp("\t0x%04x /* %4u */", p16[i], unsigned(i));
            if(i<p16.size()) fp << ',';
            fp << '\n';
        }
    }
#endif

    const uint32_t Next32 = Prime::Next<uint32_t>( 65536 );
    std::cerr << "Next32 = " << Next32 << std::endl;
    Y_CHECK( Prime::Test(Next32) );


}
Y_UDONE()

