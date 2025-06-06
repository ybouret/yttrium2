
#include "y/memory/dead-pool.hpp"
#include "y/utest/run.hpp"
#include "y/core/linked/pool.hpp"
#include "y/memory/page.hpp"

using namespace Yttrium;

Y_UTEST(memory_dead_pool)
{

    Memory::DeadPool pool(12);


    pool.cache(10);


}
Y_UDONE()
