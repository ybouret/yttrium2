
#include "y/utest/run.hpp"
#include "y/system/hardware.hpp"
#include <cerrno>

using namespace Yttrium;

Y_UTEST(system_hardware)
{
    std::cerr << "NumProcs=" << Hardware::NumProcs() << std::endl;
}
Y_UDONE()


