//! \file

#ifndef Y_MultiThreadedObject_Included
#define Y_MultiThreadedObject_Included 1

#include "y/threading/locker.hpp"
#include "y/ability/lockable.hpp"

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

        explicit MultiThreadedObject();                   //!< setup
        virtual ~MultiThreadedObject() noexcept;          //!< cleanup
        MultiThreadedObject(const MultiThreadedObject &); //!< as setup

    private:
        friend class Threading::Locker<MultiThreadedObject>;
        Y_Disable_Assign(MultiThreadedObject); //!< discarding
        Lockable * const authorization;        //!< new Concurrent::Mutex
    };

}

#endif // !Y_MultiThreadedObject_Included

