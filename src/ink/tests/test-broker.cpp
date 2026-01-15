#include "y/ink/broker.hpp"
#include "y/utest/run.hpp"
#include "y/concurrent/api/simd/crew.hpp"

using namespace Yttrium;

Y_UTEST(broker)
{
    Concurrent::Processor proc = new Concurrent::Crew( Concurrent::Site::Default );
}
Y_UDONE()

