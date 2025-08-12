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
        for(size_t n=1;n<=1;++n)
        {
            Matrix<T> a(n,n);
            Matrix<T> u(n,n), v(n,n);
            Vector<T> w(n,0); Y_ASSERT(n==w.size());

            FillWith<T>::Mat(ran,a);
            

        }

    }
}

Y_UTEST(algebra_svd)
{
    Random::MT19937 ran;

    testSVD<float>(ran);
}
Y_UDONE()
