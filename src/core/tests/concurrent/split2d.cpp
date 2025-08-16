
#include "y/concurrent/split/2d.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;
using namespace Concurrent;

Y_UTEST(concurrent_split2d)
{

    typedef V2D<int> VTX;

    Split::In2D<int> in2d( VTX(1,1), VTX(7,5) );

    const size_t total = in2d.items;
    for(size_t n=1;n<=8;++n)
    {
        std::cerr << "---- #" << n << std::endl;
        in2d.boot(n);
        size_t count =0;
        while(Split::Tile<int> * tile = in2d.next())
        {
            std::cerr << "[+] " << *tile << std::endl;
            count += tile->items;
            delete tile;
        }
        Y_ASSERT(total==count);
    }


}
Y_UDONE()
