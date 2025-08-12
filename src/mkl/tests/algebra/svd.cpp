#include "y/mkl/algebra/svd.hpp"
#include "y/utest/run.hpp"
#include "../../../core/tests/main.hpp"
#include "y/container/sequence/vector.hpp"

using namespace Yttrium;
using namespace MKL;


namespace {

    template <typename T>
    static inline
    void testSVD(Random::Bits &ran)
    {
        SVD<T> svd;
        for(size_t n=1;n<=2;++n)
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
