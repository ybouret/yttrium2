//! \file

#ifndef Y_MultiThreadedHandle_Included
#define Y_MultiThreadedHandle_Included 1

#include "y/threading/locker.hpp"

namespace Yttrium {


    //__________________________________________________________________________
    //
    //
    //! Multit-Threaded class using a Singleton's access
    //
    //__________________________________________________________________________
    template <typename SINGLETON>
    class MultiThreadedHandle
    {
    public:
        typedef Threading::Locker<MultiThreadedHandle> Lock; //!< alias

        inline explicit MultiThreadedHandle() : authorization( & SINGLETON::Instance().access ) {} //!< setup
        inline virtual ~MultiThreadedHandle() noexcept { Coerce(authorization) = 0; }              //!< cleanup

    private:
        Y_Disable_Copy_And_Assign(MultiThreadedHandle); //!< discardingb
        friend class Threading::Locker<MultiThreadedHandle>;
        Lockable * const authorization; //!< & SINGLETON:: access
    };
    
}

#endif
