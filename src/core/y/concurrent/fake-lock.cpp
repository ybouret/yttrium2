
#include "y/concurrent/fake-lock.hpp"

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

        void FakeLock:: doLock()    noexcept {}
        void FakeLock:: doUnlock()  noexcept {}
        bool FakeLock:: doTryLock() noexcept { return true; }

    }

}
