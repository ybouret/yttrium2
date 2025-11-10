
#include "y/concurrent/api/pipeline/queue/leader.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        Leader:: Leader(const size_t sz) :
        mutex(), chief(), size(sz)
        {
        }
        
        Leader:: ~Leader() noexcept
        {
        }
        
    }

}
