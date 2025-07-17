
#include "y/mkl/api/almost-equal.hpp"
#include "y/utest/run.hpp"
#include "y/ascii/convert.hpp"

using namespace Yttrium;
using namespace MKL;

Y_UTEST(mkl_almost_equal)
{

    if(argc>2)
    {
        const float x = ASCII::Convert::To<float>(argv[1],"x");
        const float y = ASCII::Convert::To<float>(argv[2],"y");
        std::cerr << "x=" << x << ", y=" << y << std::endl;
        std::cerr << "almost-equal=" << MKL::Kernel::ScalarAreAlmostEqual(x,y) << std::endl;
    }
}
Y_UDONE()

