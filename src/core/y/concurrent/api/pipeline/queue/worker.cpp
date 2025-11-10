#include "y/concurrent/api/pipeline/queue/worker.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        Worker:: ~Worker() noexcept {}

        Worker:: Worker(Leader &     ld,
                        const size_t rk) :
        Context(ld.mutex,ld.size,rk),
        mutex(ld.mutex),
        chief(ld.chief),
        block(),
        task(0),
        next(0),
        prev(0),
        thread( Thread::Run<Leader>, &ld )
        {
        }

    }

}


