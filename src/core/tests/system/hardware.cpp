
#include "y/utest/run.hpp"
#include "y/system/hardware.hpp"
#include <cerrno>

using namespace Yttrium;

Y_UTEST(system_hardware)
{
    std::cerr << "NumProcs=" << Hardware::NumProcs() << std::endl;
#if defined(_MSC_VER)
    std::cerr << "_MSC_VER=" << _MSC_VER << std::endl;
#endif
}
Y_UDONE()


