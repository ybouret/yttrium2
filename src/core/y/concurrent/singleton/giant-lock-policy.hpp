
//! \file

#ifndef Y_Concurrent_Singleton_GiantLockPolicy_Included
#define Y_Concurrent_Singleton_GiantLockPolicy_Included 1


#include "y/lockable.hpp"

namespace Yttrium
{

    class GiantLockPolicy
    {
    public:
        explicit GiantLockPolicy();
        virtual ~GiantLockPolicy() noexcept;

    protected:
        Lockable &policyLock;

    private:
        Y_Disable_Copy_And_Assign(GiantLockPolicy);
    };


}

#endif
