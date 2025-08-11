#include "y/jive/syntax/node/internal.hpp"

namespace Yttrium
{

    namespace Jive
    {

        namespace Syntax
        {

            InternalNode:: ~InternalNode() noexcept
            {
            }

            InternalNode:: InternalNode() noexcept:
            Node(IsInternal)
            {
            }

            InternalNode * Node::Make()
            {
                return new InternalNode();
            }

            void InternalNode:: restore(Lexer &lexer) noexcept
            {
                while(size) {
                    tail->restore(lexer);
                    delete popTail();
                }
            }

            InternalNode & InternalNode :: operator<<(Node * const node)
            {
                return * ( Coerce(pushTail(node)->sire) = this );
            }
        }
    }

}

