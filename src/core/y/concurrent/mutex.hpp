//! \file

#ifndef Y_Concurrent_Mutex_Included
#define Y_Concurrent_Mutex_Included 1

#include "y/ability/latch.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        class Condition;

        //______________________________________________________________________
        //
        //
        //
        //! MUTual EXclusion for threads
        //
        //
        //______________________________________________________________________
        class Mutex : public Latch
        {
        public:
            class Code;

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Mutex();           //!< initialize
            virtual ~Mutex() noexcept;  //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual bool tryLock() noexcept;
            virtual void lock()    noexcept;
            virtual void unlock()  noexcept;


        private:
            Y_Disable_Copy_And_Assign(Mutex); //!< discading
            Code * const code;                //!< platform specific
            friend class Condition;

        };
    }
}

#endif // !Y_Concurrent_Mutex_Included

