

#include "y/mkl/leap.hpp"
#include "y/utest/run.hpp"
#include "y/random/mt19937.hpp"
#include "y/random/in2d.hpp"

using namespace Yttrium;
using namespace MKL;



Y_UTEST(mkl_leap)
{
    Random::MT19937 ran;

    {
        Leap<float> l(0.0f, 1.0f), m(l);
        std::cerr << l << " / " << m << std::endl;
        l.lower = -1.0f;
        m = l;
        std::cerr << l << " / " << m << std::endl;
    }

    {
        Leap<const double> l(0,1), m(l);
        std::cerr << l << " / " << m << std::endl;

    }




}
Y_UDONE()

