
#include "y/pointer/reject-null.hpp"
#include "y/system/error.hpp"
#include <cassert>
#include <cerrno>

namespace Yttrium
{
    namespace Smart
    {
        RejectNull:: ~RejectNull() noexcept
        {

        }

        RejectNull:: RejectNull(const char * const name,
                                const void * const addr) noexcept
        {
            assert(0!=name);
            if(!addr) Libc::Error::Critical(EINVAL, "NULL address for %s",name);
        }

    }

}

