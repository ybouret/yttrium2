#include "y/concurrent/split/1d.hpp"
#include "y/container/cxx/series.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;
using namespace Concurrent;

Y_UTEST(concurrent_split1d)
{
    const size_t offset = 1;
    const size_t length = 8;
    const size_t nmax   = 10;

    CxxSeries< Split::Segment<size_t> > segments(nmax);

    for(size_t nproc=1;nproc<=nmax;++nproc)
    {
        std::cerr << "nproc=" << nproc << std::endl;
        Concurrent::Split::In1D(segments,offset,length,nproc);
        std::cerr << segments << std::endl;
    }

}
Y_UDONE()
