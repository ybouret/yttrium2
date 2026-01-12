
#if defined(_MSC_VER)
#pragma warning ( disable : 4464 )
#endif

#include "y/mkl/tao/broker/upper-diagonal.hpp"
#include "y/utest/run.hpp"
#include "../../../core/tests/main.hpp"
#include "y/concurrent/api/simd/crew.hpp"


using namespace Yttrium;
using namespace MKL;




Y_UTEST(tao_d)
{

    Random::MT19937          ran;
    Concurrent::Processor    cpu = new Concurrent::Crew( Concurrent::Site::Default );
    Tao::UpperDiagonalEngine eng = new Tao::UpperDiagonalSpawn( cpu );

}
Y_UDONE()

