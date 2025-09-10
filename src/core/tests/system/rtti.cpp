#include "y/system/rtti.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(system_rtti)
{

    System::RTTI::Display(std::cerr);
}
Y_UDONE()

