
#if defined(_MSC_VER)
#pragma warning ( disable : 4464 )
#endif

#include "y/mkl/tao/broker/upper-diagonal.hpp"
#include "y/utest/run.hpp"
#include "../../../core/tests/main.hpp"
#include "y/concurrent/api/simd/crew.hpp"


using namespace Yttrium;
using namespace MKL;


namespace
{
    template <typename T> static inline
    void doUDT(Random::Bits &                  ran,
               const Tao::UpperDiagonalEngine &eng)
    {
        Tao::UpperDiagonalBroker<T> broker(eng);
    }
}

Y_UTEST(tao_d)
{

    Random::MT19937          ran;
    Concurrent::Processor    cpu = new Concurrent::Crew( Concurrent::Site::Default );
    Tao::UpperDiagonalEngine eng = new Tao::UpperDiagonalSpawn( cpu );


    doUDT<float>(ran,eng);


}
Y_UDONE()

