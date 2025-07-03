#include "y/mkl/complex.hpp"
#include "y/mkl/xreal.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

namespace
{


    static int test3()
    {
        int a[] = {10, 12, 5};

        Sorting::Sort3(a,Sign::Increasing<int>);

        for (int i = 0; i < 3; i++)
            std::cerr << a[i] << " ";
        std::cerr << std::endl;
        return 0;
    }
}

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

    test3();


    std::cerr << MKL::Pythagoras<float>(-5,4,-1) << std::endl;


}
Y_UDONE()



