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

