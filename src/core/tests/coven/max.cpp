

#include "y/coven/tribes.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

namespace
{
    static inline apn AltMax(const size_t n)
    {
        apn sum = 0;
        for(size_t k=1;k<=n;++k) sum += apn::Factorial(n) / apn::Factorial(k-1);
        return sum;
    };

    static inline apn AltMax2(const size_t n)
    {
        const apz _1 = 1;
        apq rhs = 0;

        for(size_t k=1;k<=n;++k)
            rhs += apq(_1,apn::Factorial(k-1));

        std::cerr << "( rhs(" << n << ")=" << rhs.to<double>() << ")";

        rhs *= apn::Factorial(n);
        return rhs.numer.n;
    };

}

Y_UTEST(coven_max)
{
    for(size_t n=1;n<=10;++n)
    {
        std::cerr << n << " => " << Coven::Tribes::MaxFor(n) << " / " << AltMax(n) << " / " << AltMax2(n) << std::endl;
    }


}
Y_UDONE()

