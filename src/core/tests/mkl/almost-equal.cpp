
#include "y/mkl/api/almost-equal.hpp"
#include "y/utest/run.hpp"
#include "y/ascii/convert.hpp"
#include "y/mkl/complex.hpp"

using namespace Yttrium;
using namespace MKL;

namespace
{
    template <typename T>
    static inline
    void showCoeff(const char * const id)
    {
        std::cerr << id << std::endl;
        const T eps = Numeric<T>::EPSILON;
        const T min = Numeric<T>::MIN;
        std::cerr << "eps=" << eps << ", min=" << min << std::endl;

    }

#define SHOW_COEFF(T) showCoeff<T>( #T )

}

Y_UTEST(mkl_almost_equal)
{

    SHOW_COEFF(float);
    SHOW_COEFF(double);
    SHOW_COEFF(long double);


    if(argc>2)
    {
        const float x = ASCII::Convert::To<float>(argv[1],"x");
        const float y = ASCII::Convert::To<float>(argv[2],"y");
        std::cerr << "x=" << x << ", y=" << y << std::endl;
        std::cerr << "almost-equal=" << MKL::AlmostEqual<float>::Are(x,y) << std::endl;

        {
            const Complex<float> X(x,y);
            const Complex<float> Y(y,x);
            std::cerr << "X=" << X << ", Y=" << Y << std::endl;
            std::cerr << "almost-equal=" << MKL::AlmostEqual<Complex<float>>::Are(X,Y) << std::endl;
        }

    }
}
Y_UDONE()

