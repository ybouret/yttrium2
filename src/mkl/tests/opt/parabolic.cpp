#include "y/mkl/opt/parabolic.hpp"
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
    void testParabolic(Random::Bits &ran)
    {
        const T   amplitude(3);

        std::cerr << std::endl;
        while(true)
        {
            Triplet<T> x = { amplitude*ran.symm<T>(), amplitude*ran.symm<T>(), amplitude*ran.symm<T>() };
            Triplet<T> f = { F(x.a), F(x.b), F(x.c) };
            x.sort(f);
            Y_ASSERT(x.isIncreasing());
            if(!f.isLocalMinimum()) continue;

            std::cerr << "[#] " << x << " : " << f << std::endl;
            for(size_t i=0;i<10;++i)
            {
                ParabolicOptimization<T>::Step(F<T>,x,f);
            }
            std::cerr << "[#] " << x << " : " << f << std::endl;
            break;
        }
    }

}

Y_UTEST(opt_parabolic)
{
    Random::ParkMiller ran;
    
    testParabolic<float>(ran);
    return 0;

    testParabolic<double>(ran);
    testParabolic<long double>(ran);

    testParabolic<XReal<float> >(ran);
    testParabolic<XReal<double> >(ran);
    testParabolic<XReal<long double> >(ran);

}
Y_UDONE()
