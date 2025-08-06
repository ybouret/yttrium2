
#include "y/jive/lexical/base.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Lexical
        {

            Base:: ~Base() noexcept
            {

            }

            Base:: Base() : pdb( new Dictionary() ), nil() {}
            
        }

    }

}
