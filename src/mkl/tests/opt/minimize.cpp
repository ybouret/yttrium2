
#include "y/mkl/opt/optimize.hpp"
#include "y/mkl/opt/bracket.hpp"
#include "y/utest/run.hpp"
#include "y/random/park-miller.hpp"
#include "y/string/env.hpp"

using namespace Yttrium;
using namespace MKL;

namespace
{
    template <typename T>
    static inline T F(T x)
    {
        const T fac(3);
        return x*x*x*x - fac*x*x + x*x*x - x;
    }

    template <typename T>
    static inline
    void testMinimize(Random::Bits &ran)
    {
        std::cerr << std::endl;
        const T   amplitude(3);
        const T   _0(0);
        Triplet<T> x = { ran.symm<T>() * amplitude, _0, ran.symm<T>()*amplitude };
        Triplet<T> f = { F(x.a), _0, F(x.c) };

        std::cerr << "x=" << x << "; f=" << f << std::endl;
        if( Bracket<T>::Inside(F<T>,x,f) )
        {
            std::cerr << "Look for Local Min" << std::endl;
            std::cerr << "x=" << x << "; f=" << f << std::endl;
            const T x_opt = Optimize<T>::Run(F<T>,x,f);
            std::cerr << "Found F(" << x_opt << ")=" << f.b << std::endl;
        }
        else
        {
            std::cerr << "Global Min at " << x.a << " : " << f.a << std::endl;
        }

    }

}

Y_UTEST(opt_minimize)
{
    Random::ParkMiller ran;

    testMinimize<float>(ran);

#if 0
    testParabolic<double>(ran);
    testParabolic<long double>(ran);

    testParabolic<XReal<float> >(ran);
    testParabolic<XReal<double> >(ran);
    testParabolic<XReal<long double> >(ran);
#endif

}
Y_UDONE()
