
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
    }

}
