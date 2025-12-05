
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
            Concurrent::Divide::Tile2D<int> tile(nproc,i,box);
        }
    }



}
Y_UDONE()
