#include "y/concurrent/divide/1d.hpp"
#include "y/utest/run.hpp"



using namespace Yttrium;




Y_UTEST(concurrent_div1d)
{
    const uint16_t length = 8;
    const uint16_t offset = 1;
    const size_t   nmax   = 10;

    for(size_t nproc=1;nproc<=nmax;++nproc)
    {
        std::cerr << std::endl << "nproc=" << nproc << std::endl;
        uint16_t sum = 0;
        for(size_t i=1;i<=nproc;++i)
        {
            Concurrent::Divide::Tile1D<uint16_t> segment(nproc,i,length,offset);
            std::cerr << "\t" << segment << std::endl;
            sum += segment.length;
            {
                const Concurrent::Member                   member(nproc,i-1);
                const Concurrent::Divide::Tile1D<uint16_t> tile(member,length,1);
                Y_ASSERT(tile==segment);
                Y_ASSERT(tile.utmost == segment.utmost);
            }
        }
        Y_ASSERT(length == sum);

        {
            Concurrent::Divide::Tiles1D<uint32_t> tiles(nproc,length,1);
            std::cerr << "tiles=" << tiles << std::endl;
        }
    }


}
Y_UDONE()
