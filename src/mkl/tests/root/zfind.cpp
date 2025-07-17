#include "y/mkl/root/zfind.hpp"
#include "y/utest/run.hpp"
#include "y/stream/libc/output.hpp"

using namespace Yttrium;
using namespace MKL;

namespace
{
    static inline
    float F(float x)
    {
        return 0.2f + 0.7f * cosf( x*x - 0.01f);
    }


    template <typename T, template <typename> class ZFIND> static
    inline void testZFind( )
    {

        Triplet<T> x = { 0, 0, 2 };
        Triplet<T> f = { F(x.a), 0, F(x.c) };
        ZFIND<T>   zfind;
        typename ZFIND<T>::Handle hx,hf;

        if( zfind.found(F,hx,hf,x,f) )
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

        }


    }
}

Y_UTEST(root_zfind)
{

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

    testZFind<float,ZFind>();
    testZFind<double,ZFind>();



}
Y_UDONE()

