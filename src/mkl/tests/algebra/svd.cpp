#if defined(_MSC_VER)
#pragma warning ( disable : 4464 )
#endif

#include "y/mkl/algebra/svd.hpp"
#include "y/utest/run.hpp"
#include "../../../core/tests/main.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/mkl/tao/3.hpp"
#include "y/container/light-array.hpp"
#include "y/mkl/api/fcpu.hpp"

using namespace Yttrium;
using namespace MKL;


namespace {

    template <typename T>
    static inline
    void testSVD(Random::Bits &ran)
    {
        Cameo::Addition<T> xadd;
        SVD<T> svd;
        for(size_t n=1;n<=8;++n)
        {
            Matrix<T> a(n,n);
            Matrix<T> u(n,n), v(n,n);
            Vector<T> w(n,0); Y_ASSERT(n==w.size());

            FillWith<T>::Mat(ran,a);

            std::cerr << "a=" << a << std::endl;
            if(!svd.build(u, w, v, a)) {
                std::cerr << "couldn't build SVD" << std::endl;
            }
            std::cerr << "u=" << u << std::endl;
            std::cerr << "w=diagm(" << w << ")" << std::endl;
            std::cerr << "v=" << v << std::endl;

            Matrix<T> vT(TransposeOf,v);

            Matrix<T> M(n,n);
            {
                Matrix<T> wv(n,n);
                Tao::DMul(wv,w,vT);
                Tao::MMul(xadd,M,u,wv);
            }
            std::cerr << "M=" << M << std::endl;
            Tao::MSub(M,a);

            {
                const LightArray<T> arr(M(),M.items);
                const T             rms2 = Tao::Norm2(xadd,arr) / FCPU<T>::Cast(M.items);
                const T             rms  = Sqrt<T>::Of(rms2);
                std::cerr << "rms=" << double(rms) << std::endl;
            }

            Vector<T> b(n,0);
            FillWith<T>::Seq(ran,b);
            Vector<T> x(n,0);

            svd.solve(u,w,v,b,x);
            std::cerr << "x =" << x << std::endl;
            std::cerr << "b =" << b << std::endl;

            Vector<T> ax(n,0);
            Tao::Mul(xadd,ax,a,x);
            std::cerr << "ax=" << ax << std::endl;

            {
                const T rms2 = Tao::Norm2(xadd,ax,b);
                const T             rms  = Sqrt<T>::Of(rms2);
                std::cerr << "rms=" << double(rms) << std::endl;
            }
        }

    }
}

Y_UTEST(algebra_svd)
{
    Random::MT19937 ran;

    testSVD<float>(ran);
    testSVD< XReal<double> >(ran);

}
Y_UDONE()
