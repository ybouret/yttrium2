
#include "y/memory/dead-pool.hpp"
#include "y/utest/run.hpp"
#include "y/core/linked/pool.hpp"
#include "y/memory/page.hpp"

using namespace Yttrium;

Y_UTEST(memory_dead_pool)
{
    Y_SIZEOF(Core::PoolOf<Memory::Page>);
    Y_SIZEOF(Memory::DeadPool);
}
Y_UDONE()
