//! \file

#ifndef Y_System_AtExit_Included
#define Y_System_AtExit_Included 1


#include "y/type/ints.hpp"
#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace System
    {
        struct AtExit
        {
            typedef uint16_t      Priority;
            
            typedef void (*Proc)(void *);

            Proc      proc;
            void     *args;
            Priority  prio;
        };
    }
}

#endif

