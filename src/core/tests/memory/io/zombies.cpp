
#include "y/memory/io/netherworld.hpp"
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



    Memory::Netherworld<int,SingleThreadedClass>                  st_pool;
    Memory::Netherworld<int,MultiThreadedObject>                  mt_pool;
    Memory::Netherworld<int,GlobalMultiThreaded>                  sg_pool;
    Memory::Netherworld<int,MultiThreadedHandle<Memory::System> > ms_pool;


    int * a = st_pool.conjure(); Memory::TrackDown::Print(std::cerr,a) << std::endl;
    int * b = mt_pool.conjure(); Memory::TrackDown::Print(std::cerr,b) << std::endl;
    int * c = sg_pool.conjure(); Memory::TrackDown::Print(std::cerr,c) << std::endl;
    int * d = ms_pool.conjure(); Memory::TrackDown::Print(std::cerr,d) << std::endl;

    st_pool.banish(a);
    mt_pool.banish(b);

    sg_pool.banish(c);

    ms_pool.banish(d);



}
Y_UDONE()

