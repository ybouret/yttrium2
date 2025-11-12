#include "y/concurrent/api/pipeline/queue/worker.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        Worker:: ~Worker() noexcept {}


        static inline
        void RunLeader(void * const args) noexcept
        {
            assert(args);
            static_cast<Leader *>(args)->run();
        }

        Worker:: Worker(Leader &     ld,
                        const size_t rk) :
        Context(ld.mutex,ld.size,rk),
        mutex(ld.mutex),
        chief(ld.chief),
        block(),
        task(0),
        next(0),
        prev(0),
        thread( RunLeader, &ld )
        {
        }

        void Worker:: suspend() noexcept
        {
            block.wait(mutex);
        }

        void Worker:: resume() noexcept
        {
            block.signal();
        }

        void Worker:: operator()(void) noexcept
        {
            assert(task);
            mutex.unlock();
            task->perform(*this);
            mutex.lock();
        }


    }

}


