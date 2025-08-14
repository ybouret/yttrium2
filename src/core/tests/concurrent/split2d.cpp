
#include "y/concurrent/split/2d.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;
using namespace Concurrent;

Y_UTEST(concurrent_split2d)
{

    typedef V2D<int> VTX;

    Split::In2D<int> in2d( VTX(1,1), VTX(10,5) );
    

}
Y_UDONE()
