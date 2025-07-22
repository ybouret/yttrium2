#include "y/mkl/algebra/lu.hpp"
#include "y/utest/run.hpp"
#include "../../../core/tests/main.hpp"



using namespace Yttrium;

namespace
{
    template <typename T>
    static inline void testLU(Random::Bits &ran)
    {

        MKL::LU<T> lu;

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
                break;
            }
        }

    }
}

Y_UTEST(algebra_lu)
{
    Random::MT19937 ran;
    testLU<float>(ran);

}
Y_UDONE()
