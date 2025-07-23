

#include "y/mkl/algebra/lu.hpp"
#include "y/utest/run.hpp"
#include "../../../core/tests/main.hpp"
#include "y/container/cxx/array.hpp"
#include "y/mkl/tao/3.hpp"

using namespace Yttrium;

namespace
{

    template <typename T, typename U>
    static inline
    void testAdjoint(Random::Bits &ran)
    {
        std::cerr << "--------" << std::endl;
        MKL::LU<T> lu;
        Cameo::Addition<T> xadd;

        for(size_t n=1;n<=3;++n)
        {
            const Matrix<U> M(n,n);
            FillWith<U>::Mat(ran,Coerce(M));
            std::cerr << "M=" << M << std::endl;
            const T dM = lu.determinant(M);
            const U dMu = dM;
            std::cerr << "dM =" << dM  << std::endl;
            std::cerr << "dM =" << dMu << std::endl;
            Matrix<T> A(n,n);  lu.adjoint(A,M);
            std::cerr << "A=" << A << std::endl;
            Matrix<T> IA(n,n);
            if( lu.inverse(IA,M) )
            {
                Matrix<T> P(n,n);
                MKL::Tao::MMul(xadd,P,A,M);
                P /= dM;
                std::cerr << "P=" << P << std::endl;
            }

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
