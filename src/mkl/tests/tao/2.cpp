
#if defined(_MSC_VER)
#pragma warning ( disable : 4464 )
#endif

#include "y/mkl/tao/2.hpp"
#include "y/utest/run.hpp"
#include "../../../core/tests/main.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/concurrent/api/simd/crew.hpp"
#include "y/container/matrix.hpp"

using namespace Yttrium;
using namespace MKL;

namespace
{

    template <typename T> static inline
    void doTest(Random::Bits &ran, Tao::LinearEngine &eng)
    {
        Tao::LinearBroker<T> broker(eng);

        size_t    n = 10;
        size_t    m = 5;
        Matrix<T> a(n,m);
        Vector<T> rhs(m,0);
        Vector<T> seq(n,0);
        Vector<T> par(n,0);

        FillWith<T>::Mat(ran,a);
        FillWith<T>::Seq(ran,rhs);


        Tao::Mul(broker.xadd(),seq,a,rhs);
        Tao::Mul(broker,       par, a, rhs);
        std::cerr << "a=" << a << std::endl;
        std::cerr << "rhs=" << rhs << std::endl;

        std::cerr << "seq=" << seq << std::endl;
        std::cerr << "par=" << par << std::endl;
    }

}

Y_UTEST(tao_2)
{
    Random::MT19937       ran;
    Concurrent::Processor cpu = new Concurrent::Crew( Concurrent::Site::Default );
    Tao::LinearEngine     eng = new Tao::LinearSpawn( cpu );

    doTest<float>(ran,eng);

}
Y_UDONE()

