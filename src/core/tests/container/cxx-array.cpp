
#include "y/container/cxx/array.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;


Y_UTEST(container_cxx_array)
{
    CxxArray<int> arr(0,1);

    std::cerr << "arr=" << arr << std::endl;
}
Y_UDONE()

