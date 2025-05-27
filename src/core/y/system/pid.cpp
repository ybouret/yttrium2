
#include "y/system/pid.hpp"
#include "y/system/platform.hpp"

#if defined(Y_BSD)
#include <unistd.h>
#endif

#if defined(Y_WIN)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

namespace Yttrium
{
    namespace System
    {
        uint64_t ProcessID:: Get()
        {

#if defined(Y_WIN)
            return ::GetCurrentProcessId();
#endif


#if defined(Y_BSD)
            union
            {
                uint64_t q;
                pid_t    p;
            } alias = { 0 };
            alias.p = getpid();
            return alias.q;
#endif
        }
    }

}

