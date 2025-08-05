
#include "y/jive/lexical/rule.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Lexical
        {

            Rule:: ~Rule() noexcept
            {
            }

            Rule:: Rule(const Rule &_) noexcept :
            Object(),
            name(_.name),
            motif(_.motif)
            {
            }
            
        }

    }

}
