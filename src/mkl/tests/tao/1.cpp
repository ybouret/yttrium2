
#include "y/mkl/tao/1.hpp"
#include "y/utest/run.hpp"
#include "../../../core/tests/main.hpp"
#include "y/container/sequence/vector.hpp"

using namespace Yttrium;
using namespace MKL;

namespace
{
    template <typename T>
    static inline
    void testTao1(Random::Bits &ran)
    {
        typedef typename ScalarFor<T>::Type ScalarType;
        Cameo::Addition<ScalarType> SAdd;

        const size_t n = 1+ran.leq<size_t>(10);

        Vector<T> lhs(WithAtLeast,n), rhs(WithAtLeast,n);
        for(size_t i=n;i>0;--i) {
            lhs << Gen<T>::New(ran);
            rhs << Gen<T>::New(ran);
        }

        std::cerr << "lhs=" << lhs << std::endl;
        std::cerr << "rhs=" << rhs << std::endl;

        std::cerr << "lhs2= " << Tao::Norm2(SAdd,lhs) << std::endl;
        std::cerr << "rhs2= " << Tao::Norm2(SAdd,rhs) << std::endl;

        std::cerr << "nrm2=" << Tao::Norm2(SAdd,lhs,rhs) << std::endl;

    }
}

Y_UTEST(tao_1)
{
    Random::MT19937 ran;

    testTao1<float>(ran);
    testTao1< XReal<double> >(ran);
    testTao1< Complex<long double> >(ran);
    testTao1< apq >(ran);



}
Y_UDONE()

