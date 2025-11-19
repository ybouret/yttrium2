
//! \file

#ifndef Y_Concurrent_Condition_Included
#define Y_Concurrent_Condition_Included 1

#include "y/concurrent/mutex.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        //______________________________________________________________________
        //
        //
        //
        //! Condition variable
        //
        //
        //______________________________________________________________________
        class Condition
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            class Code;
            Condition();           //!< initialize
            ~Condition() noexcept; //!< cleanup

            void wait(Mutex &) noexcept; //!< wait on a LOCKED mutex, wake up on a LOCKED mutex
            void signal()      noexcept; //!< wake-up a waiting thread
            void broadcast()   noexcept; //!< wake-up all waiting threads
            
        private:
            Y_Disable_Copy_And_Assign(Condition); //!< discarding
            Code * const code;                    //!< platform dependent condition
        };

        //! helper to wait if test is true (until a thread signal the condition)
#define Y_Thread_Suspend_If(TEST,CV,MUTEX) do { Y_Lock(MUTEX); if(TEST) CV.wait(MUTEX); } while(false)

    }

}
#endif // !Y_Concurrent_Condition_Included

