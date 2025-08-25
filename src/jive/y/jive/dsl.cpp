#include "y/jive/dsl.hpp"

namespace Yttrium
{

    namespace Jive
    {

        DSL:: ~DSL() noexcept
        {

        }

        const String & DSL:: key()      const noexcept { return *lang; }
        const char *   DSL:: callSign() const noexcept { return lang->c_str(); }

    }

}

