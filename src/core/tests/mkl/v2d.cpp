
#include "y/mkl/v2d.hpp"
#include "y/utest/run.hpp"
#include "y/random/mt19937.hpp"
#include "y/random/in2d.hpp"

using namespace Yttrium;
using namespace MKL;



Y_UTEST(mkl_v2d)
{
    Random::MT19937 ran;

    V2D<float> v;
    std::cerr << v << std::endl;
    v = Random::OnCircle< V2D<float> >(ran);
    std::cerr << v << std::endl;
}
Y_UDONE()

