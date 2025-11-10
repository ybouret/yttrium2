
//! \file

#ifndef Y_Concurrent_Queue_Squad_Included
#define Y_Concurrent_Queue_Squad_Included 1

#include "y/concurrent/api/pipeline/queue.hpp"
#include "y/core/linked/list/raw.hpp"
#include "y/container/cxx/series.hpp"
#include "y/concurrent/api/pipeline/queue/worker.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        class Queue:: Squad : public Leader
        {
        public:
            typedef RawListOf<Worker> Workers;

            explicit Squad(const Site &);
            virtual ~Squad() noexcept;


            void enqueue(TaskIDs       & taskIDs,
                         const Kernels & kernels,
                         Task::ID      & counter);


            Workers           waiting; //!< waiting workers
            Workers           running; //!< running workers
            Tasks             pending; //!< pending tasks
            CxxSeries<Worker> workers; //!< memory for workers
            size_t            ready;   //!< count sync

        private:
            Y_Disable_Copy_And_Assign(Squad);
            void         quit() noexcept;
            virtual void run()  noexcept;
        };

    }

}

#endif // !Y_Concurrent_Queue_Squad_Included

