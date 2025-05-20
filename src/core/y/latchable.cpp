
#include "y/latchable.hpp"


namespace Yttrium
{
    Latchable:: Latchable() noexcept : Lockable() {}
    Latchable:: ~Latchable() noexcept {}

    bool Latchable:: tryLock() noexcept
    {
        if( doTryLock() )
        {
            ++Coerce(count);
            return true;
        }
        else
            return false;
    }

}
