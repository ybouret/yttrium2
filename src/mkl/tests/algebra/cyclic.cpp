#if defined(_MSC_VER)
#pragma warning ( disable : 4464 )
#endif

#include "y/mkl/algebra/cyclic.hpp"
#include "y/utest/run.hpp"
#include "../../../core/tests/main.hpp"
#include "y/container/cxx/array.hpp"
#include "y/mkl/tao/2.hpp"

#include <typeinfo>

using namespace Yttrium;
using namespace MKL;


namespace
{
    template <typename T>
    static inline void TestCyclic(Random::Bits &ran, const size_t nmax=10)
    {
        std::cerr << "-- using " << typeid(T).name() << std::endl;
        typedef typename ScalarFor<T>::Type ScalarType;
        const ScalarType s0 = 0;

        Cameo::Addition<T>          xadd;
        Cameo::Addition<ScalarType> sadd;


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
                    cy.a[i] = Gen<T>::New(ran);
                    do
                    {
                        cy.b[i] = Gen<T>::New(ran);
                    }
                    while( Fabs<T>::Of(cy.b[i]) <= s0 );
                    cy.c[i] = Gen<T>::New(ran);
                    r[i]    = Gen<T>::New(ran);
                }

                const uint32_t chk = cy.crc32();
                cy.alpha = Gen<T>::New(ran);
                cy.beta  = Gen<T>::New(ran);
                Y_ASSERT(cy.crc32()==chk);

            }
            while( !cy.solve(u,r) );

            Matrix<T> M(n,n);
            cy.sendTo(M);


            Tao::Mul(xadd,v,M,u);
            cy.mul(xadd,w,u);
            const ScalarType residue1 = Tao::Norm2(sadd,v,r);
            const ScalarType residue2 = Tao::Norm2(sadd,w,r);

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

Y_UTEST(algebra_cyclic)
{
    Random::MT19937 ran;

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


    TestCyclic<apq>(ran,8);

}
Y_UDONE()
