
#include "y/container/cxx/array.hpp"
#include "y/utest/run.hpp"
#include "y/apex/rational.hpp"

using namespace Yttrium;


Y_UTEST(container_cxx_array)
{
    {
        CxxArray<int> arr(0,1);
        std::cerr << "arr=" << arr << std::endl;
    }

    {
        const CxxArray<apq> arr(10,2);
        std::cerr << "arr=" << arr << std::endl;

        CxxArray<apq> cpy(arr);
        std::cerr << "cpy=" << arr << std::endl;

        Y_CHECK(arr==cpy);

    }
}
Y_UDONE()

