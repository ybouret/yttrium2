
//! \file


#ifndef Y_Jive_Syntax_Category_Included
#define Y_Jive_Syntax_Category_Included 1

#include "y/system/compiler.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Syntax
        {

            //! named category
            enum Category
            {
                IsTerminal, //!< for terminal rule/node
                IsInternal  //!< for internal rule/node
            };
        }
    }
}

#endif
