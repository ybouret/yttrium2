
#include "y/memory/io/netherworld.hpp"
#include "y/memory/allocator/system.hpp"
#include "y/utest/run.hpp"

#include "y/threading/single-threaded-class.hpp"
#include "y/threading/global-multi-threaded.hpp"

using namespace Yttrium;

Y_UTEST(memory_io_zombies)
{

    Memory::Netherworld<int,SingleThreadedClass>                  st_pool;
    Memory::Netherworld<int,MultiThreadedObject>                  mt_pool;
    Memory::Netherworld<int,GlobalMultiThreaded>                  sg_pool;
    Memory::Netherworld<int,MultiThreadedHandle<Memory::System> > ms_pool;

    st_pool.conjure();
    mt_pool.conjure();
    sg_pool.conjure();
    ms_pool.conjure();


}
Y_UDONE()

