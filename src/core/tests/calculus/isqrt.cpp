#include "y/calculus/isqrt.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(calculus_isqrt)
{

    for(int i=0;i<=100;++i)
    {
        const int s = IntegerSquareRoot(i);
        std::cerr << i << " => " << s << std::endl;
        Y_ASSERT(s*s<=i);
        Y_ASSERT((s+1)*(s+1)>i);
    }
}
Y_UDONE()

