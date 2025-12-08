

#include "y/concurrent/api/simd/spawn.hpp"
#include "y/concurrent/divide/2d.hpp"
#include "y/concurrent/api/simd/sole.hpp"
#include "y/concurrent/api/simd/crew.hpp"
#include "y/utest/run.hpp"



using namespace Yttrium;



namespace
{
    typedef Concurrent::Divide::CxxTiles1D<uint64_t> In1D;
    typedef In1D::Tile T1D;

    void DoSomething(Lockable &sync, const T1D &t)
    {
        {
            Y_Lock(sync);
            Y_Giant_Lock();
            (std::cerr << "DoSomething at " << t << std::endl).flush();
        }

    }
}


Y_UTEST(concurrent_spawn)
{


    Concurrent::Processor st = new Concurrent::Sole();
    Concurrent::Processor mt = new Concurrent::Crew(Concurrent::Site::Default);

    T1D::ConstType  value = 100;
    {
        Concurrent::Spawn<In1D> spawn(st,value);
        spawn.run(DoSomething);
    }

    {
        Concurrent::Spawn<In1D> spawn(mt,value);
        spawn.run(DoSomething);
    }






}
Y_UDONE()
