
#ifndef Y_Concurrent_Alone_Included
#define Y_Concurrent_Alone_Included 1

#include "y/concurrent/api/pipeline.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        //______________________________________________________________________
        //
        //
        //
        //! Sequential pipeline
        //
        //
        //______________________________________________________________________
        class Alone : public Pipeline
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const char * const CallSign; //!< "Concurrent::Alone"

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Alone();
            virtual ~Alone() noexcept;

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual const char * callSign() const noexcept;
            

        private:
            class Code;
            Y_Disable_Copy_And_Assign(Alone); //!< discarding
            Code * const code;
            
            virtual void enqueue(Task * const) noexcept;
        };
    }

}

#endif // !Y_Concurrent_Alone_Included
