#include "y/mkl/complex.hpp"
#include "y/mkl/xreal.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(antelope_add)
{
    std::cerr << MKL::Pythagoras<float>(3,4) << std::endl;


    {
        Complex<long double> z(3,4);
        std::cerr << z.abs() << std::endl;
    }

    {
        Complex< XReal<double> > z(3,4);
        std::cerr << z.abs() << std::endl;

    }

}
Y_UDONE()



