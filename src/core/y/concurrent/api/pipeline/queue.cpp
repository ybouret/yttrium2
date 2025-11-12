#include "y/concurrent/api/pipeline/queue/squad.hpp"
#include "y/type/destroy.hpp"

namespace Yttrium
{
    namespace Concurrent
    {



        const char * const Queue:: CallSign = "Concurrent::Queue";

        Queue:: Queue(const Site site) :
        Pipeline(site->size(),CallSign),
        squad( new Squad(site) )
        {
        }

        Queue:: ~Queue() noexcept
        {
            assert(squad);
            Destroy(squad);
        }

        const char * Queue:: callSign() const noexcept
        {
            return CallSign;
        }


        void Queue:: flush() noexcept
        {
            assert(squad);
            squad->flush();
        }

        void Queue :: prune() noexcept
        {
            assert(squad);
            squad->prune();
        }

        void Queue:: enqueue(TaskIDs &taskIDs, const Kernels &kernels)
        {
            assert(squad);
            squad->enqueue(taskIDs,kernels,counter);
        }
    }

}
