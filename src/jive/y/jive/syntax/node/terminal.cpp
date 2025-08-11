
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

            TerminalNode:: TerminalNode(InternalNode * const from,
                                        Lexeme *       const lx) noexcept :
            Node(IsTerminal,from),
            lexeme(lx)
            {
            }

            TerminalNode * Node::Make(InternalNode *const from, Lexeme *const lx)
            {
                assert(0!=lx);
                try { return new TerminalNode(from,lx); }
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


