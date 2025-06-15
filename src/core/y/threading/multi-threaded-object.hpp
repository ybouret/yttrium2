//! \file

#ifndef Y_MultiThreadedObject_Included
#define Y_MultiThreadedObject_Included 1

#include "y/threading/locker.hpp"

namespace Yttrium {

    class Lockable;

    //__________________________________________________________________________
    //
    //
    //
    //! use a new Mutex as authorization
    //
    //
    //__________________________________________________________________________
    class MultiThreadedObject
    {
    public:
        typedef Threading::Locker<MultiThreadedObject> Lock; //!< alias

        explicit MultiThreadedObject();           //!< setup
        virtual ~MultiThreadedObject() noexcept;  //!< cleanup

    private:
        friend class Threading::Locker<MultiThreadedObject>;
        Y_Disable_Copy_And_Assign(MultiThreadedObject); //!< discarding
        Lockable * const authorization;                 //!< new Concurrent::Mutex
    };

}

#endif

