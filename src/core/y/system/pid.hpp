//! \file

#ifndef Y_System_PID_Included
#define Y_System_PID_Included 1

#include "y/system/compiler.hpp"

namespace Yttrium
{
    namespace System
    {
        struct ProcessID
        {
            static uint64_t Get();
        };
    }
}

#endif

