#if defined(_MSC_VER)
#pragma warning ( disable : 4464 )
#endif

#include "y/mkl/algebra/tridiag.hpp"
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
    static inline void TestTriDiag(Random::Bits &ran, const size_t nmax=10)
    {
        std::cerr << "-- using " << typeid(T).name()  << std::endl;
        typedef typename ScalarFor<T>::Type ScalarType;

        Cameo::Addition<T>           xadd;
        Cameo::Addition<ScalarType>  sadd;

        for(size_t n=1;n<=nmax;++n)
        {
            std::cerr << "--   n=" << n << std::endl;
            TriDiag<T>  tr(n);
            CxxArray<T> u(n);
            CxxArray<T> r(n);
            CxxArray<T> v(n);
            CxxArray<T> w(n);

            do
            {
                for(size_t i=1;i<=n;++i)
                {
                    tr.a[i] = Gen<T>::New(ran);
                    tr.b[i] = Gen<T>::New(ran);
                    tr.c[i] = Gen<T>::New(ran);
                    r[i]    = Gen<T>::New(ran);
                }
            }
            while( !tr.solve(u,r) );

            Matrix<T> M(n,n);
            tr.sendTo(M);

            Tao::Mul(xadd,v, M, u);
            tr.mul(xadd,w,u);

            const ScalarType residue1 = Tao::Norm2(sadd,v,r);
            const ScalarType residue2 = Tao::Norm2(sadd,w,r);

            //std::cerr << "M=" << M << std::endl;
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

Y_UTEST(algebra_tridiag)
{
    Random::MT19937 ran;

    TestTriDiag<float>(ran);
    TestTriDiag<double>(ran);
    TestTriDiag<long double>(ran);


    TestTriDiag< XReal<float> >(ran);
    TestTriDiag< XReal<double> >(ran);
    TestTriDiag< XReal<long double> >(ran);

    TestTriDiag< Complex<float> >(ran);
    TestTriDiag< Complex<double> >(ran);
    TestTriDiag< Complex<long double> >(ran);

    TestTriDiag< Complex< XReal<float> > >(ran);
    TestTriDiag< Complex< XReal<double> > >(ran);
    TestTriDiag< Complex< XReal<long double> > >(ran);


    TestTriDiag<apq>(ran,8);


}
Y_UDONE()
