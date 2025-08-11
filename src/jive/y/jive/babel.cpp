
#include "y/jive/babel.hpp"

namespace Yttrium
{
    namespace Jive
    {
        Babel:: ~Babel() noexcept
        {
        }

        Babel:: Babel() :
        lexicalDB()
        {

            lexicalInit();
        }

    }
}
