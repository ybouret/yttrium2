
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
            //! Activity of a terminal
            //
            //__________________________________________________________________
            enum Activity
            {
                Regular, //!< appears in tree
                Divider  //!< syntax only
            };

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

                //! setup
                /**
                 \param rid rule name
                 \param role activity
                 \param spec univocal
                 */
                template <typename RID> inline
                explicit Terminal(const RID    & rid,
                                  const Activity role,
                                  const bool     spec) :
                Rule(rid,IsTerminal,UUID),
                activity(role),
                univocal(spec)
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
                virtual bool           accepts(Y_Jive_XRule_Args) const;
                virtual OutputStream & vizDecl(OutputStream &)    const;
                virtual OutputStream & vizPost(OutputStream &)    const;

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const Activity activity; //!< activity for syntax tree
                const bool     univocal; //!< univocal or not
                
            private:
                Y_Disable_Copy_And_Assign(Terminal); //!< discarding
            };


        }
    }

}

#endif

