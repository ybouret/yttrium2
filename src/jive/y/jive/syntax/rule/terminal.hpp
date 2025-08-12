
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
            //__________________________________________________________________
            //
            //
            //
            //! rule with matching lexeme name
            //
            //
            //__________________________________________________________________
            class Terminal : public Rule
            {
            public:
                static const uint32_t UUID = Y_FOURCC('T', 'E', 'R', 'M'); //!< alias

                //! setup \param r rule name
                template <typename RID> inline
                explicit Terminal(const RID &r) :
                Rule(r,IsTerminal,UUID)
                {
                }

                //! cleanup
                virtual ~Terminal() noexcept;

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                virtual bool accepts(Y_Jive_XRule_Args) const;


            private:
                Y_Disable_Copy_And_Assign(Terminal); //!< discarding
            };


        }
    }

}

#endif

