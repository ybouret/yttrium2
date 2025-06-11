//! \file

#ifndef Y_MultiThreadedObject_Included
#define Y_MultiThreadedObject_Included 1

#include "y/threading/locker.hpp"

namespace Yttrium {

    class Lockable;

    class MultiThreadedObject
    {
    public:
        typedef Threading::Locker<MultiThreadedObject> Lock;

        explicit MultiThreadedObject();
        virtual ~MultiThreadedObject() noexcept;

    private:
        Y_Disable_Copy_And_Assign(MultiThreadedObject);
        friend Lock;
        Lockable * const access;
    };

}

#endif

