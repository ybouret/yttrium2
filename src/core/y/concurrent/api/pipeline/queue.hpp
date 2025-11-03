

#ifndef Y_Concurrent_Queue_Included
#define Y_Concurrent_Queue_Included 1

#include "y/concurrent/api/pipeline.hpp"
#include "y/concurrent/thread/site.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        //______________________________________________________________________
        //
        //
        //
        //! Parallel pipeline
        //
        //
        //______________________________________________________________________
        class Queue : public Pipeline
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const CallSign; //!< "Concurrent::Queue"

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Queue(const Site); //!< setup
            virtual ~Queue() noexcept;  //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual const char * callSign()            const noexcept;
            virtual void         flush()                     noexcept;
            virtual void         purge()                     noexcept;
            
        private:
            class Coach;
            class Player;
            Y_Disable_Copy_And_Assign(Queue);   //!< discarding
            Coach * const coach;                //!< inner code

            virtual Lockable &   getLockable()               const noexcept;
            virtual Task::Status getUnlocked(const Task::ID) const noexcept;
            virtual void         enqueueTask(Task * const)         noexcept;
            virtual void         enqueueBand(Task::Dict &             dict,
                                             const Readable<Kernel> & todo);
        };
    }

}

#endif // !Y_Concurrent_Queue_Included
