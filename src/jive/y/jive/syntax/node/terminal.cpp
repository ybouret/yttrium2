
#include "y/jive/syntax/node/terminal.hpp"
#include "y/jive/syntax/rule/terminal.hpp"

#include "y/type/destroy.hpp"
#include "y/stream/output.hpp"

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

            

            TerminalNode:: TerminalNode(const Terminal &r, Lexeme * const lx) noexcept :
            Node(IsTerminal,r),
            lexeme(lx)
            {
            }


            TerminalNode * Node:: Make(const Terminal &r, Lexeme *const l)
            {
                assert(0!=l);
                try { return new TerminalNode(r,l); }
                catch(...){ delete l; throw; }
            }

            void TerminalNode:: restore(Lexer &lexer) noexcept
            {
                if(lexeme)
                {
                    lexer.store(lexeme);
                    Coerce(lexeme) = 0;
                }
            }

            OutputStream & TerminalNode:: viz(OutputStream &fp) const
            {
                nodeName(fp) << '[';
                Label(fp,*rule.name);
                fp << ",shape=box";
                return Endl( fp << ']' );
            }

            const Terminal * TerminalNode:: lastTerm()    const noexcept
            {
                assert(rule.isTerminal());
                return dynamic_cast<const Terminal *>( &rule );
            }

        }

    }

}


