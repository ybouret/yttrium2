
#include "y/concurrent/singleton/giant-lock-policy.hpp"

namespace Yttrium
{


    GiantLockPolicy:: ~GiantLockPolicy() noexcept
    {
    }

    GiantLockPolicy:: GiantLockPolicy()  :
    policyLock( Lockable::Giant() )
    {

    }
    
}

