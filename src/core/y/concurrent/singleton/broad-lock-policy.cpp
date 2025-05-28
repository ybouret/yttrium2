


#include "y/concurrent/singleton/broad-lock-policy.hpp"
#include "y/concurrent/nucleus.hpp"

namespace Yttrium
{


    BroadLockPolicy:: ~BroadLockPolicy() noexcept
    {
    }

    BroadLockPolicy:: BroadLockPolicy()  :
    access( Concurrent::Nucleus::Instance().queryLockable()  )
    {

    }

}

