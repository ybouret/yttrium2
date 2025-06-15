//! \file

#ifndef Y_MultiThreadedHandle_Included
#define Y_MultiThreadedHandle_Included 1

#include "y/threading/locker.hpp"

namespace Yttrium {


    //__________________________________________________________________________
    //
    //
    //
    //! Multit-Threaded class using another lockable
    //
    //
    //__________________________________________________________________________
    class MultiThreadedHandle
    {
    public:
        typedef Threading::Locker<MultiThreadedHandle> Lock; //!< alias

        inline explicit MultiThreadedHandle( Lockable &handle ) noexcept : authorization( &handle)  {} //!< setup \param handle PERSISTENT lockable
        inline virtual ~MultiThreadedHandle() noexcept { Coerce(authorization) = 0; }         //!< cleanup

    private:
        friend class Threading::Locker<MultiThreadedHandle>;
        Y_Disable_Copy_And_Assign(MultiThreadedHandle); //!< discarding
        Lockable * const authorization;                 //!< & handle
    };
    
}

#endif
