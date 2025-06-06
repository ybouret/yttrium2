
#include "y/memory/dead-pool.hpp"
#include "y/memory/page.hpp"
#include "y/core/utils.hpp"
#include "y/memory/stealth.hpp"
#include "y/core/linked/pool.hpp"

namespace Yttrium
{
    namespace Memory
    {

        namespace
        {
            typedef Core::PoolOf<Page> PoolType;
        }

        DeadPool:: ~DeadPool() noexcept
        {
        }


        DeadPool:: DeadPool(const size_t blockSize) :
        guild( MaxOf<size_t>(blockSize,sizeof(Page)) ),
        entry(0),
        words()
        {
            new ( Coerce(entry) = Y_Memory_BZero(words) ) PoolType();
        }
    }

}

