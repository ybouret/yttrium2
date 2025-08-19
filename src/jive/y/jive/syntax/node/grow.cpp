
#include "y/jive/syntax/node/internal.hpp"

namespace Yttrium
{

    namespace Jive
    {

        namespace Syntax
        {
            void Node:: Grow(Node *&tree, Node *const node) noexcept
            {
                assert(0!=node);
                if(0==tree)
                {
                    tree = node;
                }
                else
                {
                    assert(tree->isInternal());
                    InternalNode * const target = dynamic_cast<InternalNode *>(tree); assert(target);
                    *target << node;
                }
            }
        }

    }

}
