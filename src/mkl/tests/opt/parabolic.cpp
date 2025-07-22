#include "y/mkl/opt/parabolic.hpp"
#include "y/utest/run.hpp"
#include "y/random/park-miller.hpp"
#include "y/string/env.hpp"
#include "y/stream/libc/output.hpp"

using namespace Yttrium;
using namespace MKL;

namespace
{
    template <typename T>
    static inline T F(T x)
    {
        //return T(0.4)*(x-T(0.1))*(x-T(0.1));

        const T fac(3);
        return x*x*x*x - fac*x*x + x*x*x - x;
    }


    template <typename T>
    static inline void appendTo(const char * const fileName,
                                const Triplet<T> &x,
                                const Triplet<T> &f,
                                const unsigned    i)
    {
        AppendFile fp(fileName);
        fp("%.15g %.15g %u\n", double(x.a), double(f.a), i );
        fp("%.15g %.15g %u\n", double(x.b), double(f.b), i );
        fp("%.15g %.15g %u\n", double(x.c), double(f.c), i );
        fp("%.15g %.15g %u\n", double(x.a), double(f.a), i );
        fp("\n");
    }

    template <typename T>
    static inline
    void testParabolic(Random::Bits &ran, const char * const fileName = 0)
    {
        const T   amplitude(2.5);

        if(fileName) OutputFile::Overwrite(fileName);

        std::cerr << std::endl;
        while(true)
        {
            Triplet<T> x = { amplitude*ran.symm<T>(), amplitude*ran.symm<T>(), amplitude*ran.symm<T>() };
            Triplet<T> f = { F(x.a), F(x.b), F(x.c) };
            x.sort(f);
            Y_ASSERT(x.isIncreasing());
            if(!f.isLocalMinimum()) continue;

            std::cerr << "[#] " << x << " : " << f << std::endl;
            if(fileName) appendTo(fileName,x,f,1);

            for(unsigned i=1;i<=1;++i)
            {
                ParabolicStep<T>::Tighten(F<T>,x,f);
                if(fileName) appendTo(fileName,x,f,i+1);
            }
            std::cerr << "[#] " << x << " : " << f << std::endl;
            break;
        }
    }

}

Y_UTEST(opt_parabolic)
{
    Random::ParkMiller ran;
    ParabolicStepVerbose = Environment::Flag("VERBOSE");


    testParabolic<float>(ran,"para-f.dat");
    return 0;

    testParabolic<double>(ran);
    testParabolic<long double>(ran);

    testParabolic<XReal<float> >(ran);
    testParabolic<XReal<double> >(ran);
    testParabolic<XReal<long double> >(ran);

}
Y_UDONE()
