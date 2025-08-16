
#include "y/concurrent/split/2d.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;
using namespace Concurrent;

Y_UTEST(concurrent_split2d)
{

    typedef V2D<int> VTX;

    Split::In2D<int> in2d( VTX(1,1), VTX(2,2) );

    for(size_t n=1;n<=8;++n)
    {
        std::cerr << "---- #" << n << std::endl;
        in2d.boot(n);
        while(in2d.next())
        {
        }
    }


}
Y_UDONE()
