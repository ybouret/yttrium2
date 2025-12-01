
#include "y/calculus/prime/test.hpp"
#include "y/utest/run.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/core/print-tableau.hpp"

using namespace Yttrium;

template <typename T> static inline
T Transform(const T &x)
{
    return x;
}

Y_UTEST(calculus_primes)
{

    for(unsigned i=0;i<=1000;++i)
    {
        if( Prime::Test(i) ) std::cerr << i << std::endl;
    }

    Vector<unsigned> p8;
    // precomputing
    for(unsigned i=0;i<256;++i)
    {
        if( Prime::Test(i) ) p8 << i;
    }

    Core::PrintTableau(std::cerr, p8.begin(), p8.size(), Transform<unsigned> ) << std::endl;
    std::cerr << "#8=" << p8.size() << std::endl;

    Vector<uint32_t> p16;
    for(uint32_t i=256;i<65536;++i)
    {
        if( Prime::Test(i) ) p16 << i;
    }
    std::cerr << "#16=" << p16.size() << std::endl;


}
Y_UDONE()

