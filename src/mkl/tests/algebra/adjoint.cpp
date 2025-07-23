

#include "y/mkl/algebra/lu.hpp"
#include "y/utest/run.hpp"
#include "../../../core/tests/main.hpp"
#include "y/container/cxx/array.hpp"


using namespace Yttrium;

namespace
{

    template <typename T, typename U>
    static inline
    void testAdjoint(Random::Bits &ran)
    {
        MKL::LU<T> lu;

        for(size_t n=1;n<=5;++n)
        {
            Matrix<U> M(n,n);
            FillWith<U>::Mat(ran,M);
            std::cerr << "M=" << M << std::endl;
            const T dM = lu.determinant(M);
            std::cerr << "dM=" << dM << std::endl;
        }
    }

}

Y_UTEST(algebra_adjoint)
{
    Random::MT19937 ran;

    testAdjoint<float,float>(ran);
    
    testAdjoint<apq, apz>(ran);

}
Y_UDONE()
