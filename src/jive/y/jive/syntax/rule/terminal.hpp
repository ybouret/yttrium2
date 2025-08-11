
//! \file

#ifndef Y_Jive_Syntax_TerminalRule_Included
#define Y_Jive_Syntax_TerminalRule_Included 1

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
                static const uint32_t UUID = Y_FOURCC('T', 'E', 'R', 'M');

                template <typename RID> inline
                explicit Terminal(const RID &r) :
                Rule(r,IsTerminal,UUID)
                {
                }
                
                virtual ~Terminal() noexcept;
                
            private:
                Y_Disable_Copy_And_Assign(Terminal);
            };


        }
    }

}

#endif

