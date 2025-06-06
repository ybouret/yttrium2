#include "y/system/wall-time.hpp"
#include "y/utest/run.hpp"
#include <cerrno>

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
}
Y_UDONE()
