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
        return Squared(Squared(x-T(0.1))) + T(0.7) + T(0.5) * x;
    }

    template <typename T>
    static inline
    void testParabolic(Random::Bits &ran)
    {

        while(true)
        {
            Triplet<T> x = { ran.symm<T>(), ran.symm<T>(), ran.symm<T>() };
            Triplet<T> f = { F(x.a), F(x.b), F(x.c) };
            x.sort(f);
            Y_ASSERT(x.isIncreasing());
            if(!f.isLocalMinimum()) continue;

            std::cerr << x << " : " << f << std::endl;

            ParabolicOptimization<T>::Step(F<T>,x,f);
            std::cerr << x << " : " << f << std::endl;
            ParabolicOptimization<T>::Step(F<T>,x,f);
            std::cerr << x << " : " << f << std::endl;

            break;
        }
    }

}

Y_UTEST(opt_parabolic)
{
    Random::ParkMiller ran;
    ParabolicOptimizationVerbose = Environment::Flag("VERBOSE");

    testParabolic<float>(ran);

}
Y_UDONE()
