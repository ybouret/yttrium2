#include "y/mkl/algebra/eigen.hpp"
#include "../../core/tests/main.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;
using namespace MKL;

template <typename T>
static inline void TestBalance(Random::Bits &ran)
{
    std::cerr << std::endl;
    std::cerr << "TestBalance" << std::endl;
    Eigen::Balance<T> balance;
    for(size_t n=1;n<=3;++n)
    {
        Matrix<T> a0(n,n);
        FillWith<T>::Mat(ran,a0);
        std::cerr << "a0=" << a0 << std::endl;
        Matrix<T> a = a0;
        balance(a);
        std::cerr << "a=" << a << std::endl;
    }
}

template <typename T>
static inline void TestHessenberg(Random::Bits &ran)
{
    std::cerr << std::endl;
    std::cerr << "TestHessenberg" << std::endl;
    Eigen::Hessenberg<T> hessenberg;
    for(size_t n=1;n<=3;++n)
    {
        Matrix<T> a0(n,n);
        FillWith<T>::Mat(ran,a0);
        std::cerr << "a0=" << a0 << std::endl;
        Matrix<T> a = a0;
        hessenberg(a);
        std::cerr << "a=" << a << std::endl;
    }
}


Y_UTEST(algebra_eigen)
{
    Random::MT19937 ran;
    TestBalance<float>(ran);
    TestBalance<double>(ran);

    TestHessenberg<float>(ran);

}
Y_UDONE()

