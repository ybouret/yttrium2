
//! \file

#ifndef Y_Concurrent_Queue_Leader_Included
#define Y_Concurrent_Queue_Leader_Included 1

#include "y/concurrent/mutex.hpp"
#include "y/concurrent/condition.hpp"
#include "y/concurrent/runnable.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        //______________________________________________________________________
        //
        //
        //
        //! Necessary to initialize worker
        //
        //
        //______________________________________________________________________
        class Leader : public Runnable
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Leader(const size_t); //!< setup with required size
            virtual ~Leader() noexcept;    //!< cleanup

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            Mutex        mutex; //!< common mutes
            Condition    chief; //!< communication condition
            const size_t size;  //!< number of workers to build

        private:
            Y_Disable_Copy_And_Assign(Leader); //!< discarding
        };

    }

}

#endif // !Y_Concurrent_Queue_Leader_Included

