#include "y/ability/lockable.hpp"
#include "y/system/error.hpp"
#include "y/check/usual.hpp"
#include <cassert>

namespace Yttrium
{

    Lockable:: Lockable() noexcept : count(0)
    {
    }

    Lockable:: ~Lockable() noexcept
    {
        assert( 0 == count || Die("wrong unlock count") );
    }

    void Lockable:: lock() noexcept
    {
        doLock();
        ++Coerce(count);
    }

    void Lockable:: unlock() noexcept
    {
        assert(count>0 || Die("no previous lock") );
        doUnlock();
        --Coerce(count);
    }

    bool Lockable:: isLocked() const noexcept
    {
        return count>0;
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
