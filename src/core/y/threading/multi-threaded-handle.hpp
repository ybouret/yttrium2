//! \file

#ifndef Y_MultiThreadedHandle_Included
#define Y_MultiThreadedHandle_Included 1

#include "y/threading/locker.hpp"

namespace Yttrium {


    template <typename SINGLETON>
    class MultiThreadedHandle
    {
    public:
        typedef Threading::Locker<MultiThreadedHandle> Lock;

        inline explicit MultiThreadedHandle() : access( & SINGLETON::Instance().access ) {}
        inline virtual ~MultiThreadedHandle() noexcept { Coerce(access) = 0; }
    private:
        Y_Disable_Copy_And_Assign(MultiThreadedHandle);
        friend Lock;
        Lockable * const access;
    };
    
}

#endif
