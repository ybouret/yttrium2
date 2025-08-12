
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

            Node:: Node(const Category t, const Rule &r) noexcept :
            type(t),
            rule(r),
            sire(0),
            next(0),
            prev(0)
            {
            }

            void Node:: Restore(Node * const node, Lexer &lexer) noexcept
            {
                node->restore(lexer);
                delete node;
            }

            void Node:: Restore(NodeList &list, Lexer &lexer) noexcept
            {
                while( list.size ) Restore(list.popTail(),lexer);
            }

            bool Node:: isInternal() const noexcept { return IsInternal == type; }

            bool Node:: isTerminal() const noexcept { return IsTerminal == type; }
            

        }

    }

}



