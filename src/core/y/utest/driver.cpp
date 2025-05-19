#include "y/utest/driver.hpp"

namespace Yttrium
{
    namespace UTest
    {
        int Procedure::Compare(const void *const lhs, const void *const rhs) noexcept
        {
            return strcmp( static_cast<const Procedure *>(lhs)->name, static_cast<const Procedure *>(rhs)->name );
        }

    }

}
