#include "y/system/wall-time.hpp"
#include "y/utest/run.hpp"
#include <cerrno>
#include <cmath>

using namespace Yttrium;

Y_UTEST(system_wall_time)
{
    System::WallTime chrono;
    const uint64_t ini = System::WallTime::Ticks();
    std::cerr << ini << std::endl;

    while( chrono.since(ini) < 0.1 )
    {
        std::cerr << chrono.Ticks() << std::endl;
    }
    std::cerr << "ellapsed=" << chrono.since(ini) << std::endl;

    uint64_t probe = 0;
    double   sum   = 0;
    for(unsigned u=0;u<50000;++u)
    {
        Y_WallTime_Mark(&probe);
        sum += cos( double(u) );
        Y_WallTime_Gain(&probe);
    }
    std::cerr << "sum=" << sum << " in " << chrono(probe) << std::endl;

}
Y_UDONE()
