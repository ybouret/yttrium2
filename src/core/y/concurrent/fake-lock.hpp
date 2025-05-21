

//! \file

#ifndef Y_Concurrent_FakeLock_Included
#define Y_Concurrent_FakeLock_Included 1

#include "y/latchable.hpp"

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
        class FakeLock : public Latchable
        {
        public:
            explicit FakeLock() noexcept;
            virtual ~FakeLock() noexcept;

        private:
            Y_Disable_Copy_And_Assign(FakeLock); //!< discarding
            Y_Lockable_Decl();                   //!< lockable API
            Y_Latchable_Decl();                  //!< latchable API
        };

    }

}

#endif

