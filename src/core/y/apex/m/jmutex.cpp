#include "y/apex/m/jmutex.hpp"


namespace Yttrium
{

    namespace Apex
    {
        JointMutex:: ~JointMutex() noexcept
        {
        }

        JointMutex:: JointMutex() : Object(), Concurrent::Mutex(), next(0), prev(0)
        {
        }
        
    }

}

