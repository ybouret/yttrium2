
#include "y/mkl/algebra/cyclic.hpp"
#include "y/utest/run.hpp"
#include "../../../core/tests/main.hpp"
#include "y/container/cxx/array.hpp"
#include "y/mkl/tao/2.hpp"

#include <typeinfo>

using namespace Yttrium;
using namespace MKL;
#if 0
namespace
{
    template <typename T>
    static inline void TestCyclic(Random::Bits &ran, const size_t nmax=10)
    {
        std::cerr << "-- using " << typeid(T).name() << std::endl;
        typedef typename ScalarFor<T>::Type ScalarType;
        const ScalarType s0 = 0;

        Cameo::Addition<T>     xadd;
        //Tao::ComputeMod2<T> mod2;

        for(size_t n=3;n<=nmax;++n)
        {
            std::cerr << "--   n=" << n << std::endl;
            Cyclic<T>   cy(n);
            CxxArray<T> u(n);
            CxxArray<T> r(n);
            CxxArray<T> v(n);
            CxxArray<T> w(n);


            do
            {
                for(size_t i=1;i<=n;++i)
                {
                    cy.a[i] = Bring<T>::Get(ran);
                    do
                    {
                        cy.b[i] = Bring<T>::Get(ran);
                    }
                    while( Fabs<T>::Of(cy.b[i]) <= s0 );
                    cy.c[i] = Bring<T>::Get(ran);
                    r[i]    = Bring<T>::Get(ran);
                }

                const uint32_t chk = cy.crc32();
                cy.alpha = Bring<T>::Get(ran);
                cy.beta  = Bring<T>::Get(ran);
                Y_CHECK(cy.crc32()==chk);

            }
            while( !cy.solve(u,r) );

            Matrix<T> M(n,n);
            cy.sendTo(M);


            Tao::Mul(v,M,u,xm);
            cy.mul(w,u);
            const ScalarType residue1 = mod2(v,r);
            const ScalarType residue2 = mod2(w,r);

            // std::cerr << "M=" << M << std::endl;
            // std::cerr << "r=" << r << std::endl;
            // std::cerr << "u=" << u << std::endl;
            // std::cerr << "v=" << v << std::endl;
            // std::cerr << "w=" << w << std::endl;
            std::cerr << "--     residue1=" << residue1 << std::endl;
            std::cerr << "--     residue2=" << residue2 << std::endl;
        }
        std::cerr << std::endl;

    }
}
#endif

Y_UTEST(algebra_cyclic)
{
    Random::MT19937 ran;

#if 0
    TestCyclic<float>(ran);
    TestCyclic<double>(ran);
    TestCyclic<long double>(ran);


    TestCyclic< XReal<float> >(ran);
    TestCyclic< XReal<double> >(ran);
    TestCyclic< XReal<long double> >(ran);

    TestCyclic< Complex<float> >(ran);
    TestCyclic< Complex<double> >(ran);
    TestCyclic< Complex<long double> >(ran);

    TestCyclic< Complex< XReal<float> > >(ran);
    TestCyclic< Complex< XReal<double> > >(ran);
    TestCyclic< Complex< XReal<long double> > >(ran);


    TestCyclic<apq>(ran,6);
#endif

}
Y_UDONE()
