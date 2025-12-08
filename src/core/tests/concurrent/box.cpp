

#include "y/concurrent/divide/2d.hpp"
#include "y/utest/run.hpp"

#include "y/mkl/v3d.hpp"


using namespace Yttrium;




Y_UTEST(concurrent_box)
{
    {
        typedef V2D<int>             v2d;
        Concurrent::Divide::Box<v2d> box( v2d(1,1), v2d(3,5) );

        for(int i=0;i<box.count;++i)
        {
            const v2d v = box.at(i);
            std::cerr << v << std::endl;
        }

    }

    
    {
        typedef V3D<short> v3d;
        Concurrent::Divide::Box<v3d> box( v3d(1,1,1), v3d(3,5,7) );
        for(short i=0;i<box.count;++i)
        {
            const v3d v = box.at(i);
            std::cerr << v << std::endl;
        }
    }

}
Y_UDONE()
