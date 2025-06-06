
//! \file

#ifndef Y_Concurrent_Condition_Included
#define Y_Concurrent_Condition_Included 1

#include "y/concurrent/mutex.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        class Condition
        {
        public:
            class Code;
            Condition();
            ~Condition() noexcept;

            void wait(Mutex &) noexcept; //!< wait on a LOCKED mutex, wake up on a LOCKED mutex
            void signal()      noexcept; //!< wake-up a waiting thread
            void broadcast()   noexcept; //!< wake-up all waiting threads
            
        private:
            Y_Disable_Copy_And_Assign(Condition);
            Code * const code;
        };

    }

}
#endif

