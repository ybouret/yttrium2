#include "y/concurrent/api/pipeline/queue.hpp"
#include "y/type/destroy.hpp"
#include "y/type/destruct.hpp"
#include "y/concurrent/thread.hpp"
#include "y/object/school-of.hpp"
#include "y/concurrent/condition.hpp"
#include "y/core/linked/list/raw.hpp"
#include <iostream>

namespace Yttrium
{
    namespace Concurrent
    {



        const char * const Queue:: CallSign = "Concurrent::Queue";

        Queue:: Queue(const Site site) :
        Pipeline(site->size(),CallSign),
        squad(0)
        {
        }

        Queue:: ~Queue() noexcept
        {

        }

        const char * Queue:: callSign() const noexcept
        {
            return CallSign;
        }


      
    }

}
