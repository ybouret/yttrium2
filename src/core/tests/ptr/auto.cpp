
#include "y/pointer/auto.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;




Y_UTEST(ptr_auto)
{
    AutoPtr<int> ip; std::cerr << ip << std::endl;
    ip = new int(4); std::cerr << ip << std::endl;
}
Y_UDONE()
