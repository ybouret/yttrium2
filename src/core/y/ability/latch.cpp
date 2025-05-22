
#include "y/ability/latch.hpp"


namespace Yttrium
{
    Latch::  Latch() noexcept : Lockable() {}
    Latch:: ~Latch() noexcept {}

    bool Latch:: tryLock() noexcept
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
