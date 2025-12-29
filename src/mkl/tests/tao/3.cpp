#include "y/mkl/tao/broker/matrix.hpp"
#include "y/utest/run.hpp"
#include "y/random/mt19937.hpp"
//#include "../../../core/tests/main.hpp"
//#include "y/container/sequence/vector.hpp"
#include "y/concurrent/api/simd/crew.hpp"
#include "y/container/matrix.hpp"

using namespace Yttrium;
using namespace MKL;

Y_UTEST(tao_3)
{
    Random::MT19937       ran;
    Concurrent::Processor cpu = new Concurrent::Crew( Concurrent::Site::Default );
    Tao::MatrixEngine     eng = new Tao::MatrixSpawn( cpu );


}
Y_UDONE()
