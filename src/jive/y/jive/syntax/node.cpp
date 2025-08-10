
#include "y/jive/syntax/node.hpp"
#include "y/type/destruct.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Syntax
        {
            Node:: ~Node() noexcept
            {
            }

            Node:: Node(const Category t, InternalNode * const from) noexcept :
            type(t),
            sire(from),
            next(0),
            prev(0)
            {
            }

            void Node:: Restore(Node * const, Lexer &) noexcept
            {}

        }

    }

}

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

namespace Yttrium
{
    namespace Jive
    {

        namespace Syntax
        {

            InternalNode:: ~InternalNode() noexcept
            {
            }

            InternalNode:: InternalNode(InternalNode * const from) noexcept:
            Node(IsInternal,from)
            {
            }

            InternalNode * Node::Make(InternalNode *const from)
            {
                return new InternalNode(from);
            }

            void InternalNode:: restore(Lexer &lexer) noexcept
            {
                while(size) {
                    tail->restore(lexer);
                    delete popTail();
                }
            }
        }
    }

}

