

//! \file

#ifndef Y_Concurrent_Singleton_ClassLockPolicy_Included
#define Y_Concurrent_Singleton_ClassLockPolicy_Included 1


#include "y/concurrent/fake-lock.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! One Lock (Mutex) per class
    //
    //
    //__________________________________________________________________________
    class ClassLockPolicy
    {
    public:
        explicit ClassLockPolicy();
        virtual ~ClassLockPolicy() noexcept;

    protected:
        Concurrent::FakeLock policyLock; //!< for local access

    private:
        Y_Disable_Copy_And_Assign(ClassLockPolicy); //!< disarding
    };


}

#endif
