
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



