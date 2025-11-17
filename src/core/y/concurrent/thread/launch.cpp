
#include "y/concurrent/thread/launch.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        ThreadData:: ~ThreadData() noexcept {}
        

        void ThreadData:: run() noexcept {
            assert(mine);
            try { (*this.*mine)(); } catch(...) { }
        }

        Runnable & ThreadData::self() noexcept { return *this; }

    }

    namespace Concurrent
    {
        Launch:: ~Launch() noexcept
        {

        }
        
    }

}


