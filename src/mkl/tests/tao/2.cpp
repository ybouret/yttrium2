
#if defined(_MSC_VER)
#pragma warning ( disable : 4464 )
#endif

#include "y/mkl/tao/2.hpp"
#include "y/utest/run.hpp"
#include "../../../core/tests/main.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/concurrent/api/simd/crew.hpp"

using namespace Yttrium;
using namespace MKL;

namespace
{

    template <typename T> static inline
    void doTest(Random::Bits &ran, Tao::LinearEngine &eng)
    {
        Tao::LinearBroker<T> broker(eng);
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

