#include "y/mkl/api/mod2.hpp"
#include "y/utest/run.hpp"
#include "y/mkl/complex.hpp"
#include "y/mkl/v4d.hpp"

using namespace Yttrium;

namespace
{
    template <typename T>
    static inline void testMod2(const T &arg)
    {
        std::cerr << arg << " => " << MKL::Mod2<T>::Of(arg) << std::endl;
    }
}

Y_UTEST(mkl_mod2)
{
    {
        float f = -0.1f;
        testMod2(f);
    }

    {
        Complex<double> z(0.1,-0.3);
        testMod2(z);
    }

    {
        V2D<long double> v2(0.3,-0.1);
        testMod2(v2);
    }

    {
        V3D<int> v3(-1,2,-3);
        testMod2(v3);
    }

    {
        V4D<double> v4(3,-2,1,-5);
        testMod2(v4);
    }



}
Y_UDONE()


