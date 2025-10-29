#include "y/concurrent/fake-lock.hpp"
#include <cassert>

namespace Yttrium
{

    namespace Concurrent
    {
        FakeLock:: FakeLock() noexcept : count(0)
        {
        }

        FakeLock:: ~FakeLock() noexcept
        {
            assert(0==count);
        }

        void FakeLock:: lock() noexcept
        {
            ++Coerce(count);
        }

        void FakeLock:: unlock()  noexcept
        {
            assert(count>0);
            --Coerce(count);
        }

        bool FakeLock:: tryLock() noexcept
        {
            ++Coerce(count);
            return true;
        }

        
    }

}
