
#include "y/apex/api/coven/tribes.hpp"


namespace Yttrium
{

    namespace Coven
    {
        Tribes:: ~Tribes() noexcept
        {
            while(size>0)
            {
                trCache.banish(popTail());
            }
        }


        Tribes:: Tribes(const IPool        &ip,
                        const Tribe::Cache &tc) noexcept :
        idxPool(ip),
        trCache(tc)
        {
        }

    }

}
