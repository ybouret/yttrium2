

#ifndef Y_Concurrent_Queue_Included
#define Y_Concurrent_Queue_Included 1

#include "y/concurrent/api/pipeline.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        //______________________________________________________________________
        //
        //
        //
        //! Paralle pipeline
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
            explicit Queue(const size_t n);
            virtual ~Queue() noexcept;

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual const char * callSign() const noexcept;


        private:
            class Coach;
            class Player;
            Y_Disable_Copy_And_Assign(Queue); //!< discarding
            Coach * const coach; //!< inner code
        };
    }

}

#endif // !Y_Concurrent_Queue_Included
