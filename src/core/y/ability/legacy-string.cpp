
#include "y/ability/legacy-string.hpp"
#include <iostream>

namespace Yttrium
{

    LegacyString:: LegacyString() noexcept
    {
    }

    LegacyString:: ~LegacyString() noexcept
    {
    }

    std::ostream & operator<<(std::ostream &os, const LegacyString &self)
    {
        os << self.c_str();
        return os;
    }
}
