#include "y/ability/lockable.hpp"
#include "y/system/error.hpp"
#include "y/check/usual.hpp"
#include <cassert>

namespace Yttrium
{

    Lockable:: Lockable() noexcept
    {
    }

    Lockable:: ~Lockable() noexcept
    {
    }



    ScopedLock:: ScopedLock(Lockable &_) noexcept :
    host(_)
    {
        host.lock();
    }

    ScopedLock:: ~ScopedLock() noexcept
    {
        host.unlock();
    }


}
