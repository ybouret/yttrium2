#include "y/cameo/multiplication.hpp"

#include "y/mkl/complex.hpp"
#include "y/mkl/xreal.hpp"
#include "y/utest/run.hpp"
#include <cmath>

using namespace Yttrium;



namespace
{
    template <typename T> static inline
    void showMass(const T &x)
    {
        std::cerr << x << " => " << Cameo::GetFPointMass(x) << std::endl;
    }

}

Y_UTEST(cameo_mul)
{
    {
        Cameo::DirectMultiplier<apn> nmul;
        Cameo::DirectMultiplier<apz> zmul;
        Cameo::DirectMultiplier<apq> qmul;
    }

    {
        Cameo::AProxyMultiplier<int>      imul;
        Cameo::AProxyMultiplier<uint16_t> umul;
    }

    {
        const float       f = 0.1f;  showMass(f);
        const double      d = -1e-8; showMass(d);
        const long double D = 1e43;  showMass(D);
    }

    {
        const XReal<float>       f = 0.1f;  showMass(f);
        const XReal<double>      d = -1e-8; showMass(d);
        const XReal<long double> D = 1e43;  showMass(D);
    }

    {
        const Complex<float>           f(0.1f,0.2f);  showMass(f);
        const Complex< XReal<double> > d(1e-8,1e-5); showMass(d);
    }


    {
        Cameo::FPointMultiplier<float> fmul;
        fmul->cache(10);
        fmul << 1e-5f << 1e-8f << 0.1f;
        std::cerr << *fmul << std::endl;
        std::cerr << fmul.product() << std::endl;
    }

    {
        Cameo::Multiplication<apz>                zmul;
        Cameo::Multiplication<apn>                nmul;
        Cameo::Multiplication<int>                imul;
        Cameo::Multiplication<unsigned>           umul;
        Cameo::Multiplication<float>              fmul;
        Cameo::Multiplication< XReal<double> >    xmul;
        Cameo::Multiplication< Complex<double> >  cmul;
        Cameo::Multiplication< Complex< XReal<long double> > >  xcmul;

        {
            unsigned short arr[] = { 1, 10, 101, 99 };
            std::cerr << umul(arr,sizeof(arr)/sizeof(arr[0])) << std::endl;
        }
    }
}
Y_UDONE()
