#include "y/system/rtti.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(system_rtti)
{
    System::RTTI &rtti = System::RTTI::Get<float>();
    std::cerr << rtti.uuid << " / " << rtti.name() << std::endl;
    rtti.aka("float");
    std::cerr << rtti.uuid << " / " << rtti.name() << std::endl;

}
Y_UDONE()

