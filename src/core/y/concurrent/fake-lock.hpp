

//! \file

#ifndef Y_Concurrent_FakeLock_Included
#define Y_Concurrent_FakeLock_Included 1

#include "y/ability/latch.hpp"

namespace Yttrium
{

    namespace Concurrent
    {

        //______________________________________________________________________
        //
        //
        //
        //! FakeLock, counting calls only
        //
        //
        //______________________________________________________________________
        class FakeLock : public Latch
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit FakeLock() noexcept;
            virtual ~FakeLock() noexcept;

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual bool tryLock() noexcept;
            virtual void lock()    noexcept;
            virtual void unlock()  noexcept;

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const size_t count;

        private:
            Y_Disable_Copy_And_Assign(FakeLock); //!< discarding
           
        };

    }

}

#endif // !Y_Concurrent_FakeLock_Included

