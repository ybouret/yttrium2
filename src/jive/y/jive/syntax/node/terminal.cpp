
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

            String TerminalNode:: lex2str() const
            {
                String res;

                assert(rule.isTerminal());
                if( !dynamic_cast<const Terminal &>(rule).univocal )
                {
                    res += '=';
                    res += '\'' + lexeme->toString() + '\'';
                }

                return res;
            }

            OutputStream & TerminalNode:: viz(OutputStream &fp) const
            {
                nodeName(fp) << '[';
                const String label = *rule.name + lex2str();
                Label(fp,label);
                fp << ",shape=box";
                return Endl( fp << ']' );
            }

            const TerminalNode * TerminalNode:: lastTerm()    const noexcept
            {
                assert(rule.isTerminal());
                return dynamic_cast<const TerminalNode *>( this );
            }

            String TerminalNode:: str() const
            {
                return '\'' + name() + '\'' + lex2str();
            }

        }

    }

}


