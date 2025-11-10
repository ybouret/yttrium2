
//! \file

#ifndef Y_Concurrent_Queue_Worker_Included
#define Y_Concurrent_Queue_Worker_Included 1

#include "y/concurrent/api/pipeline/queue/leader.hpp"
#include "y/concurrent/api/pipeline/task.hpp"
#include "y/concurrent/thread.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        //______________________________________________________________________
        //
        //
        //
        // Necessary to initialize worker
        //
        //
        //______________________________________________________________________
        class Worker : public Context
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Worker(Leader &, const size_t); //!< initialize from leader and given rank
            virtual ~Worker() noexcept;              //!< cleanup

            //__________________________________________________________________
            //
            //
            // methods
            //
            //__________________________________________________________________
            void suspend() noexcept;
            void resume()  noexcept;
            void operator()(void) noexcept;

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            Mutex     & mutex;  //!< shared mutex
            Condition & chief;  //!< leader condition
            Condition   block;  //!< suspend condition
            Task *      task;   //!< task to perform
            Worker    * next;   //!< for list
            Worker    * prev;   //!< for list
            Thread      thread; //!< execute leader run()

        private:
            Y_Disable_Copy_And_Assign(Worker);
        };
    }

}

#endif // !Y_Concurrent_Queue_Worker_Included

