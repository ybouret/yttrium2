#include "y/chemical/type/assembly.hpp"
#include "y/core/utils.hpp"

namespace Yttrium
{
    namespace Chemical
    {
        Assembly:: ~Assembly() noexcept
        {
        }

        Assembly:: Assembly() noexcept : width(0)
        {
        }

        void Assembly:: reset() noexcept { Coerce(width) = 0; }

        void Assembly:: enroll(const Entity &en) noexcept
        {
            InSituMax(Coerce(width),en.name.size());
        }
    }

}
