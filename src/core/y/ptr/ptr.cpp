#include "y/ptr/ptr.hpp"
#include "y/system/error.hpp"
#include <cerrno>

namespace Yttrium
{
    namespace Core
    {
        Ptr:: ~Ptr() noexcept {}
        Ptr::  Ptr() noexcept {}

        const char * const Ptr:: Nil = "(nil)";

        NoNullPointer:: ~NoNullPointer() noexcept {}

        NoNullPointer:: NoNullPointer(const void * const addr) noexcept
        {
            if(!addr) Libc::Error::Critical(EINVAL,"NULL pointer detected in smart pointer");
        }
    }
}
