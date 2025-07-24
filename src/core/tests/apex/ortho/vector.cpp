#include "y/container/light-array.hpp"

#include "y/apex/api/ortho/vector.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(apex_ortho_vector)
{

    const int data[] = { 8, -2, 4 };

    LightArray<const int> arr(data,sizeof(data)/sizeof(data[0]));

    std::cerr << "arr=" << arr << std::endl;

}
Y_UDONE()



