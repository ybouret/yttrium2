
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

        void FakeLock:: doLock() noexcept
        {
            if(Trace) std::cerr << "[Lock   @" << count << "]" << std::endl;
        }

        void FakeLock:: doUnlock()  noexcept
        {
            if(Trace) std::cerr << "[Unlock @" << count << "]" << std::endl;
        }

        bool FakeLock:: doTryLock() noexcept
        {
            if(Trace) std::cerr << "[TryLock@" << count << "]" << std::endl;
            return true;
        }

        bool FakeLock::Trace = false;
    }

}
