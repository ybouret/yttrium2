
#include "y/concurrent/fake-lock.hpp"

#include <iostream>

namespace Yttrium
{

    namespace Concurrent
    {
        FakeLock:: FakeLock() noexcept
        {
        }

        FakeLock:: ~FakeLock() noexcept
        {
        }

        void FakeLock:: lock() noexcept
        {
        }

        void FakeLock:: unlock()  noexcept
        {
        }

        bool FakeLock:: tryLock() noexcept
        {
            return true;
        }

        
    }

}
