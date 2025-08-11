
//! \file

#ifndef Y_Jive_Syntax_Terminal_Included
#define Y_Jive_Syntax_Terminal_Included 1

#include "y/jive/syntax/rule.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {
            class Terminal : public Rule
            {
            public:

                virtual ~Terminal() noexcept;
                
            private:
                Y_Disable_Copy_And_Assign(Terminal);
            };


        }
    }

}

#endif

