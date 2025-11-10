
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

        //______________________________________________________________________
        //
        //
        //
        //! Squad is a Leader with Worker(s)
        //
        //
        //______________________________________________________________________
        class Queue:: Squad : public Object, public Leader
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef RawListOf<Worker> Workers;

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Squad(const Site &);
            virtual ~Squad() noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            void enqueue(TaskIDs       & taskIDs,
                         const Kernels & kernels,
                         Task::ID      & counter);

            void flush() noexcept;
            void prune() noexcept;
            
            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            Workers           waiting; //!< waiting workers
            Workers           running; //!< running workers
            Tasks             pending; //!< pending tasks
            Tasks             garbage; //!< garbage tasks ?
            CxxSeries<Worker> workers; //!< memory for workers
            size_t            ready;   //!< count sync

        private:
            Y_Disable_Copy_And_Assign(Squad);
            void         quit() noexcept;
            virtual void run()  noexcept;
            void         dispatch() noexcept;
        };

    }

}

#endif // !Y_Concurrent_Queue_Squad_Included

