
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

Y_UTEST(tao_d)
{

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
        const size_t Ki = i * n - i*(i-1)/2;
        std::cerr << " | [" << Ki << "]" << std::endl;
    }

    std::cerr << "count = " << m << " / " << ((n*(n+1))>>1) << std::endl;


    for(size_t k=1;k<=m;++k)
    {
        std::cerr << "k=" << std::setw(3) << k;
        const size_t B     = 1+n*2;
        const size_t Delta = B*B - k*8;
        const size_t twice = (B - IntegerSquareRoot(Delta));
        const size_t align = Alignment::On<2>::Ceil(twice);
        const size_t i     = align/2;
        std::cerr << ' ' << twice << " -> " << align << " -> " << i;
        std::cerr << std::endl;
    }
}
Y_UDONE()

