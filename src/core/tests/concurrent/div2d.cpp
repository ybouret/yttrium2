
#include "y/concurrent/divide/2d.hpp"
#include "y/utest/run.hpp"



using namespace Yttrium;




Y_UTEST(concurrent_div2d)
{
    typedef V2D<int> v2d;
    Concurrent::Divide::Box<v2d> box( v2d(1,1), v2d(8,5) );

    for(size_t nproc=1;nproc<=4;++nproc)
    {
        std::cerr << std::endl << "nproc=" << nproc << std::endl;
        for(size_t i=1;i<=nproc;++i)
        {
            Concurrent::Divide::Tile2D<int> tile(nproc,i-1,box);
            std::cerr << "\t| tile[" << i << "] | = " << tile.h << std::endl;
            for(int j=1;j<=tile.h;++j)
            {
                std::cerr << "\t\t" << tile[j] << std::endl;
            }
        }
    }



}
Y_UDONE()
