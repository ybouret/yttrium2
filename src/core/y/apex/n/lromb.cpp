
#include "y/apex/n/lromb.hpp"

namespace Yttrium
{
    namespace Apex
    {
        LockedReadOnlyMemoryBuffer:: ~LockedReadOnlyMemoryBuffer() noexcept
        {
            
        }

        LockedReadOnlyMemoryBuffer:: LockedReadOnlyMemoryBuffer(const Natural &n) noexcept :
        Memory::ReadOnlyBuffer(),
        host(n),
        keep(*host)
        {

        }

        size_t LockedReadOnlyMemoryBuffer:: length() const noexcept
        {
            return host.bytes();
        }

        const void * LockedReadOnlyMemoryBuffer:: ro() const noexcept
        {
            return 0;
        }

    }
}
