

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
            class Squad;

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
            virtual const char * callSign() const noexcept;
            virtual void flush() noexcept;
            virtual void prune() noexcept;

        private:
            Y_Disable_Copy_And_Assign(Queue);   //!< discarding
            Squad * const squad;                //!< inner squad
        };
    }

}

#endif // !Y_Concurrent_Queue_Included
