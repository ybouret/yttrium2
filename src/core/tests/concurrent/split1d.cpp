#include "y/concurrent/split/1d.hpp"
#include "y/container/cxx/series.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;
using namespace Concurrent;

Y_UTEST(concurrent_split1d)
{
    const int    offset = 1;
    const size_t length = 8;
    const size_t nmax   = 10;

    Split::In1D<int> in1d(offset,length);

    for(size_t nproc=1;nproc<=nmax;++nproc)
    {
        std::cerr << "nproc=" << nproc << std::endl;
        //Concurrent::Split::In1D_(segments,offset,length,nproc);
        in1d.boot(nproc);
        while( in1d.next() )
        {
            std::cerr << "\t" << in1d << std::endl;
        }
    }

}
Y_UDONE()
