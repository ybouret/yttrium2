//! \file

#ifndef Y_System_PID_Included
#define Y_System_PID_Included 1

#include "y/system/compiler.hpp"

namespace Yttrium
{
    namespace System
    {
        //! System Process Identifier
        struct ProcessID
        {
            //! get the id
            /**
             - BSD: pid_t   getpid()
             - WIN: DWORD ::GetProcessId()
             \return process-id put in uint64_t
             */
            static uint64_t Get();
        };
    }
}

#endif

