#include "y/mkl/root/zbis.hpp"
#include "y/mkl/root/zrid.hpp"
#include "y/utest/run.hpp"
#include "y/stream/libc/output.hpp"
#include "y/mkl/numeric.hpp"
#include "y/random/park-miller.hpp"
#include <cfloat>

using namespace Yttrium;
using namespace MKL;

namespace
{
    static size_t CallCount = 0;

    template <typename T>
    T F(T x)
    {
        ++CallCount;
        const T delta = x - T(0.3f);
        return -delta*delta*delta + T(0.2f);
        //const T fac(1.1);
        //return fac * x;
    }


    template <typename T, template <typename> class ZFIND> static
    inline void testZFind( Random::Bits & ran)
    {
        const T two(2);

        Triplet<T> x = { -two - ran.to<T>(), 0, two + ran.to<T>() };
        Triplet<T> f = { F(x.a), 0, F(x.c) };
        ZFIND<T>   zfind;
        CallCount = 0;
        zfind(F<T>,x,f);
        std::cerr << "[" << zfind.callSign() << "]"
        << " #call = " << CallCount
        << " x0=" << x.b
        << std::endl;
    }
}



Y_UTEST(root_zfind)
{

    Random::ParkMiller ran;

    {
        OutputFile     fp("zfind.dat");
        const float    Lmin = -5;
        const float    Lmax =  5;
        static const unsigned np   = 1000;
        for(unsigned i=0;i<=np;++i)
        {
            const float x = Lmin + ( (float)i *(Lmax-Lmin))/ (float)np;
            fp("%g %g\n", x, F(x));
        }
    }

    testZFind<float,ZBis>(ran);
    testZFind<double,ZBis>(ran);
    testZFind<long double,ZBis>(ran);
    testZFind< XReal<float>,ZBis>(ran);
    testZFind< XReal<double>,ZBis>(ran);
    testZFind< XReal<long double>,ZBis>(ran);

    std::cerr << std::endl;
    testZFind<float,ZRid>(ran);
    testZFind<double,ZRid>(ran);
    testZFind<long double,ZRid>(ran);
    testZFind< XReal<float>,ZRid>(ran);
    testZFind< XReal<double>,ZRid>(ran);
    testZFind< XReal<long double>,ZRid>(ran);

}
Y_UDONE()

