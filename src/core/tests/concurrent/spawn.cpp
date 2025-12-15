

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

    typedef Concurrent::Divide::Tiles2D<unit_t> In2D;
    typedef In2D::Tile T2D;

    void DoSomething(Lockable &sync, const T1D &t)
    {
        {
            Y_Lock(sync);
            Y_Giant_Lock();
            (std::cerr << "DoSomething at " << t <<  " with #bytes=" << t.bytes << std::endl).flush();
        }
    }

    struct CallSomeone
    {
        inline void operator()(Lockable &sync, const T1D &t)
        {
            {
                Y_Lock(sync);
                Y_Giant_Lock();
                (std::cerr << "CallSomeone at " << t << " with #bytes=" << t.bytes << std::endl).flush();
            }
        }
    };


    class Apply
    {
    public:

        Apply() noexcept
        {
        }

        inline ~Apply() noexcept
        {

        }

        void call1D(Lockable &sync, const T1D &t)
        {
            {
                Y_Lock(sync);
                Y_Giant_Lock();
                (std::cerr << "Apply::call1D  " << t << " with #byte=" << t.bytes << std::endl).flush();
            }
        }

        void call2D(Lockable &sync, const T2D &t)
        {
            {
                Y_Lock(sync);
                Y_Giant_Lock();
                (std::cerr << "Apply::call2D  " << t << " with #bytes=" << t.bytes << std::endl).flush();
            }
        }



    private:
        Y_Disable_Copy_And_Assign(Apply);
    };

}


Y_UTEST(concurrent_spawn)
{


    Concurrent::Processor st = new Concurrent::Sole();
    Concurrent::Processor mt = new Concurrent::Crew(Concurrent::Site::Default);

    T1D::ConstType  value = 100;
    CallSomeone     stuff = {};
    Apply           apply;


    {
        Concurrent::Spawn<In1D> spawn(st,value);
        spawn(DoSomething);
        spawn(stuff);
        spawn(apply, & Apply::call1D );
    }

    std::cerr << std::endl;

    {
        Concurrent::Spawn<In1D> spawn(mt,value);
        spawn.ensureLocalMemory(100);
        spawn(DoSomething);
        spawn(stuff);
        spawn(apply, & Apply::call1D );
    }

    std::cerr << std::endl;

    T2D::BoxType    box( T2D::vertex_t(0,0), T2D::vertex_t(9,5) );
    std::cerr << "box=" << box << std::endl;
    {
        Concurrent::Spawn<In2D> spawn(st,box);
        spawn(apply, & Apply::call2D );
    }
    std::cerr << std::endl;

    {
        Concurrent::Spawn<In2D> spawn(mt,box);
        spawn(apply, & Apply::call2D );
    }



}
Y_UDONE()
