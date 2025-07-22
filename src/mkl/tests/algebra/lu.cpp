
#include "y/mkl/tao/2.hpp"

#include "y/mkl/algebra/lu.hpp"
#include "y/utest/run.hpp"
#include "../../../core/tests/main.hpp"

#include "y/container/cxx/array.hpp"


using namespace Yttrium;

namespace
{
    template <typename T>
    static inline void testLU(Random::Bits &ran)
    {

        MKL::LU<T> lu;
        Cameo::Addition<T> xadd;
        for(size_t n=1;n<=5;++n)
        {
            while(true)
            {
                Matrix<T> a(n,n);
                FillWith<T>::Mat(ran,a);
                const Matrix<T> a0(a);
                if(!lu.build(a)) continue;
                std::cerr << "a=" << a0 << std::endl;

                const T d = lu.det(a);
                std::cerr << "d=" << d << std::endl;

                const CxxArray<T> b(n);
                FillWith<T>::Seq(ran,Coerce(b));
                //std::cerr << "b=" << b << std::endl;

                CxxArray<T> u(b);
                lu.solve(a,u);
                //std::cerr << "u=" << u << std::endl;

                CxxArray<T> au(n);
                MKL::Tao::Mul(xadd,au,a0,u);

                //std::cerr << "au=" << au << std::endl;
                for(size_t i=n;i>0;--i) au[i] -= b[i];
                //std::cerr << "del=" << au << std::endl;
                const T residue = MKL::Tao::Norm2(xadd,au);
                std::cerr << "residue=" << residue << std::endl;
                break;
            }
        }

    }
}

Y_UTEST(algebra_lu)
{
    Random::MT19937 ran;
    testLU<float>(ran);
    testLU<apq>(ran);

}
Y_UDONE()
