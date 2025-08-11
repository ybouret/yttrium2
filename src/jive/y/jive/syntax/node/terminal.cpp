
#include "y/jive/syntax/node/terminal.hpp"
#include "y/type/destroy.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Syntax
        {
            TerminalNode:: ~TerminalNode() noexcept
            {
                if(lexeme) Destroy(lexeme);
            }

            TerminalNode:: TerminalNode(Lexeme * const lx) noexcept :
            Node(IsTerminal),
            lexeme(lx)
            {
            }

            TerminalNode * Node:: Make(Lexeme *const lx)
            {
                assert(0!=lx);
                try { return new TerminalNode(lx); }
                catch(...){ delete lx; throw; }
            }

            void TerminalNode:: restore(Lexer &lexer) noexcept
            {
                if(lexeme)
                {
                    lexer.store(lexeme);
                    Coerce(lexeme) = 0;
                }
            }
        }

    }

}


