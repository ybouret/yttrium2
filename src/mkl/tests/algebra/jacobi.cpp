
#if defined(_MSC_VER)
#pragma warning ( disable : 4464 )
#endif

#include "y/mkl/algebra/eigen.hpp"
#include "../../core/tests/main.hpp"
#include "y/utest/run.hpp"
#include "y/container/cxx/array.hpp"
#include "y/mkl/tao/2.hpp"

using namespace Yttrium;
using namespace MKL;

template <typename T> static inline
void TestJacobi( Random::Bits &ran )
{
    Eigen::Jacobi<T> jacobi;
    Cameo::Addition<T> xadd;

    for(size_t n=1;n<=8;++n)
    {
        Matrix<T>   a(n,n);
        Matrix<T>   v(n,n);
        CxxArray<T> d(n);

        for(size_t i=1;i<=n;++i)
        {
            for(size_t j=i;j<=n;++j)
                a[i][j] = a[j][i] = Gen<T>::New(ran);
        }

        std::cerr << "a=" << a << std::endl;
        if(!jacobi(v,d,a))
        {
            std::cerr << "Couldn't diagonalize" << std::endl;
            continue;
        }
        Eigen::Sort(v,d,Sign::Increasing<T>);
        std::cerr << "v=" << v << std::endl;
        std::cerr << "d=" << d << std::endl;
        //Eigen::Sort(v,d,Fabs<T>::Increasing);
        //std::cerr << "v=" << v << std::endl;
        //std::cerr << "d=" << d << std::endl;

        CxxArray<T> u(n),au(n);
        for(size_t i=1;i<=n;++i)
        {
            const T lam = d[i];
            for(size_t j=1;j<=n;++j)
                u[j] = v[j][i];
            Tao::Mul(xadd,au,a,u);
            for(size_t j=n;j>0;--j)
            {
                au[j] -= lam *u[j];
            }
            const T rms2 = Tao::Norm2(xadd,au) / (T)n;
            const T rms  = Sqrt<T>::Of(rms2);
            std::cerr << "\trms" << i << " = " << rms << std::endl;
        }

    }
}


Y_UTEST(algebra_jacobi)
{
    Random::MT19937 ran;
    TestJacobi<float>(ran);
    TestJacobi<double>(ran);

}
Y_UDONE()
