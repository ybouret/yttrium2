

#include "y/concurrent/api/simd/spawn.hpp"
#include "y/concurrent/divide/2d.hpp"
#include "y/concurrent/api/simd/sole.hpp"
#include "y/concurrent/api/simd/crew.hpp"
#include "y/utest/run.hpp"



using namespace Yttrium;




Y_UTEST(concurrent_spawn)
{


    Concurrent::Processor st = new Concurrent::Sole();
    Concurrent::Processor mt = new Concurrent::Crew(Concurrent::Site::Default);

    typedef Concurrent::Divide::CxxTiles1D<uint64_t> T1D;
    T1D::ConstType  value = 100;
    {
        Concurrent::Spawn<T1D> spawn(st,value);
        spawn.run();
    }

    {
        Concurrent::Spawn<T1D> spawn(mt,value);
        spawn.run();
    }






}
Y_UDONE()
