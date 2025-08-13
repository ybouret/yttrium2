
#include "y/jive/syntax/category.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {
            Category_:: Category_(const Category t) noexcept : type(t)
            {

            }

            Category_:: ~Category_() noexcept
            {
            }


            bool Category_:: isInternal() const noexcept { return IsInternal == type; }

            bool Category_:: isTerminal() const noexcept { return IsTerminal == type; }
        }
    }

}

