
//! \file

#ifndef Y_Jive_Syntax_Rule_Included
#define Y_Jive_Syntax_Rule_Included 1

#include "y/jive/syntax/node/internal.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Syntax
        {
            class Rule : public Object
            {
            protected:

            public:
                virtual ~Rule() noexcept;

                const Category type;
                const Tag      name;

            private:
                Y_Disable_Copy_And_Assign(Rule);
            };
        }
    }

}

#endif

