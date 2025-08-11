

//! \file

#ifndef Y_Jive_Syntax_Internal_Included
#define Y_Jive_Syntax_Internal_Included 1

#include "y/jive/syntax/rule.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {
            class Internal : public Rule
            {
            public:

                virtual ~Internal() noexcept;

            private:
                Y_Disable_Copy_And_Assign(Internal);
            };


        }
    }

}

#endif

