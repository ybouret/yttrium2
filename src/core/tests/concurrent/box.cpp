

#include "y/concurrent/divide/2d.hpp"
#include "y/utest/run.hpp"

#include "y/mkl/v3d.hpp"


using namespace Yttrium;




Y_UTEST(concurrent_box)
{
    {
        typedef V2D<int> v2d;
        Concurrent::Divide::Box<v2d> box( v2d(1,1), v2d(8,5) );

    }


    {
        typedef V3D<short> v3d;
        Concurrent::Divide::Box<v3d> box( v3d(1,1,1), v3d(8,5,7) );

    }

}
Y_UDONE()
