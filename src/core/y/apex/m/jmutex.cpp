#include "y/apex/m/jmutex.hpp"


namespace Yttrium
{

    namespace Apex
    {
        JMutex:: ~JMutex() noexcept
        {
        }

        JMutex:: JMutex() : Object(), Concurrent::Mutex(), next(0), prev(0)
        {
        }
        
    }

}

