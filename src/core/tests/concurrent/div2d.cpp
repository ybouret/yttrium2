
#include "y/concurrent/divide/2d.hpp"
#include "y/utest/run.hpp"



using namespace Yttrium;




Y_UTEST(concurrent_div2d)
{
    typedef V2D<int> v2d;
    Concurrent::Divide::Box<v2d> box( v2d(1,1), v2d(8,5) );
    

}
Y_UDONE()
