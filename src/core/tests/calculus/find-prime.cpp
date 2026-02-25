#include "y/calculus/prime/prev.hpp"
#include "y/calculus/prime/next.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(calculus_find_prime)
{
    for(size_t i=0;i<=100;++i)
    {
        const size_t p = Prime::Next(i);
        std::cerr << i << " ==> " << p << std::endl;
    }

    for(size_t i=1;i<=100;++i)
    {
        const size_t p = Prime::Prev(i);
        std::cerr << i << " <== " << p << std::endl;
    }

}
Y_UDONE()
