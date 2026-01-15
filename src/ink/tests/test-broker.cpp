#include "y/ink/broker.hpp"
#include "y/utest/run.hpp"
#include "y/concurrent/api/simd/crew.hpp"

using namespace Yttrium;

Y_UTEST(broker)
{
    Concurrent::Processor proc = new Concurrent::Crew( Concurrent::Site::Default );
    Ink::Broker           broker(proc);

    //const Ink::Area area( Ink::Coord(0,0), Ink::Coord(10,18) );

    


}
Y_UDONE()

