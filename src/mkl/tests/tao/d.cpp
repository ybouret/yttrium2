
#if defined(_MSC_VER)
#pragma warning ( disable : 4464 )
#endif

#include "y/utest/run.hpp"
#include "../../../core/tests/main.hpp"
#include "y/string/env/convert.hpp"
#include "y/calculus/isqrt.hpp"
#include "y/calculus/alignment.hpp"


using namespace Yttrium;
using namespace MKL;

namespace
{
    static inline
    size_t GetI(const size_t n, const size_t k)
    {
        assert(k>0);
        assert(k<=n*(n+1)/2);
        const size_t B     = 1+(n<<1);
        const size_t Delta = B*B - (k<<3);
        const size_t twice = (B - IntegerSquareRoot(Delta));
        const size_t align = Alignment::On<2>::Ceil(twice);
        return align>>1;
    }

    static inline
    size_t GetK(const size_t n, const size_t i)
    {
        return i * n - (((i-1)*i)>>1);
    }

    static inline
    size_t GetJ(const size_t n, const size_t k, const size_t i)
    {
        const size_t im1 = i-1;
        return im1 + k-GetK(n,im1);
    }

}

Y_UTEST(tao_d)
{
    const size_t nmax = EnvironmentConvert::To<size_t>("nmax",100);

    for(size_t n=1;n<=nmax;++n)
    {
        std::cerr << "n=" << n << std::endl;
        size_t       k = 0;
        for(size_t i=1;i<=n;++i)
        {
            for(size_t j=i;j<=n;++j)
            {
                ++k;
                const size_t I = GetI(n,k);   Y_ASSERT(I==i);
                const size_t J = GetJ(n,k,i); Y_ASSERT(J==j);
            }
        }
    }

#if 0
    const size_t n = EnvironmentConvert::To<size_t>("n",5);
    size_t       m = 0;
    for(size_t i=1;i<=n;++i)
    {
        std::cerr << "i=" << std::setw(3) << i << ":";
        for(size_t j=i;j<=n;++j)
        {
            ++m;
            std::cerr << " " << std::setw(3) << m;
        }
        const size_t Ki = GetK(n,i);
        std::cerr << " | [" << Ki << "]" << std::endl;
    }

    std::cerr << "count = " << m << " / " << ((n*(n+1))>>1) << std::endl;


    for(size_t k=1;k<=m;++k)
    {
        std::cerr << "k=" << std::setw(3) << k;
        const size_t i = GetI(n,k);
        std::cerr << "-> i=" << std::setw(3) << i;
        const size_t j = i-1 + k - GetK(n,i-1);
        std::cerr << "-> j=" << std::setw(3) << j;

        std::cerr << std::endl;
    }
#endif

}
Y_UDONE()

