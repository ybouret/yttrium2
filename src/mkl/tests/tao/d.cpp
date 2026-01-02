
#if defined(_MSC_VER)
#pragma warning ( disable : 4464 )
#endif

#include "y/utest/run.hpp"
#include "../../../core/tests/main.hpp"
#include "y/string/env/convert.hpp"

using namespace Yttrium;
using namespace MKL;

Y_UTEST(tao_d)
{

    const size_t n = EnvironmentConvert::To<size_t>("n",5);
    size_t count = 0;
    for(size_t i=1;i<=n;++i)
    {
        for(size_t j=i;j<=n;++j)
        {
            ++count;
        }
    }

    std::cerr << "count = " << count << " / " << ((n*(n+1))>>1) << std::endl;
}
Y_UDONE()

