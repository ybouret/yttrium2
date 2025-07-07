
#include "y/apex/n/shielded.hpp"

namespace Yttrium
{
    namespace Apex
    {

        Shielded:: ~Shielded() noexcept
        {
        }

        Shielded:: Shielded() : Number(), shield() {}

        Lockable & Shielded:: operator*() const noexcept
        {
            return shield;
        }
    }

}

