#include "y/mkl/root/zbis.hpp"
#include "y/utest/run.hpp"
#include "y/stream/libc/output.hpp"
#include "y/mkl/numeric.hpp"
#include "y/random/park-miller.hpp"
#include <cfloat>

using namespace Yttrium;
using namespace MKL;

namespace
{
    template <typename T>
    T F(T x)
    {
        //return 0.2f + 0.7f * cosf( x*x - 0.01f);
        return x;
    }


    template <typename T, template <typename> class ZFIND> static
    inline void testZFind( Random::Bits & ran)
    {
        const T minusOne(-1);
        const T two(2);

        Triplet<T> x = { minusOne * ran.to<T>(), 0, two * ran.to<T>() };
        Triplet<T> f = { F(x.a), 0, F(x.c) };
        ZFIND<T>   zfind; std::cerr << "[" << zfind.callSign() << "]" << std::endl;
        typename ZFIND<T>::Handle hx,hf;

        
        if( zfind.found(F<T>,hx,hf,x,f) )
        {
            std::cerr << "zero @" << x.b << std::endl;
        }
        else
        {
            std::cerr << "lookup" << std::endl;
            Y_ASSERT(hx.neg);
            Y_ASSERT(hx.pos);
            Y_ASSERT(hf.neg);
            Y_ASSERT(hf.pos);
            Y_ASSERT(*hf.neg<0);
            Y_ASSERT(*hf.pos>0);
            zfind(F<T>,x,f);
        }


    }
}



Y_UTEST(root_zfind)
{

    Random::ParkMiller ran;

    {
        OutputFile     fp("zfind.dat");
        const float    Lmin = -5;
        const float    Lmax =  5;
        const unsigned np   = 1000;
        for(unsigned i=0;i<=np;++i)
        {
            const float x = Lmin + (i *(Lmax-Lmin))/np;
            fp("%g %g\n", x, F(x));
        }
    }

    testZFind<float,ZBis>(ran);
    //testZFind<double,ZBis>(ran);
    //testZFind<long double,ZBis>();




}
Y_UDONE()

