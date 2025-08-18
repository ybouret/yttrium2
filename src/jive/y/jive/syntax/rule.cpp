
#include "y/jive/syntax/rule.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Syntax
        {

            bool Rule::Verbose = false;
            
            Rule:: ~Rule() noexcept {}

            const String & Node:: name() const noexcept
            {
                return *rule.name;
            }

        }

    }

}


