
#include "y/memory/io/limbo.hpp"
#include "y/memory/allocator/system.hpp"
#include "y/utest/run.hpp"

#include "y/threading/single-threaded-class.hpp"
#include "y/threading/global-multi-threaded.hpp"
#include "y/threading/multi-threaded-object.hpp"
#include "y/threading/multi-threaded-handle.hpp"

#include "y/memory/track-down.hpp"


using namespace Yttrium;

Y_UTEST(memory_io_zombies)
{



    Memory::Limbo<int,SingleThreadedClass> st_pool;
    Memory::Limbo<int,MultiThreadedObject> mt_pool;
    Memory::Limbo<int,GlobalMultiThreaded> sg_pool;
    Memory::Limbo<int,MultiThreadedHandle> ms_pool( Lockable::Giant() );


    int * a = st_pool.summon(); Memory::TrackDown::Print(std::cerr,a) << std::endl;
    int * b = mt_pool.summon(); Memory::TrackDown::Print(std::cerr,b) << std::endl;
    int * c = sg_pool.summon(); Memory::TrackDown::Print(std::cerr,c) << std::endl;
    int * d = ms_pool.summon(); Memory::TrackDown::Print(std::cerr,d) << std::endl;

    st_pool.banish(a);
    mt_pool.banish(b);

    sg_pool.banish(c);

    ms_pool.banish(d);



}
Y_UDONE()

