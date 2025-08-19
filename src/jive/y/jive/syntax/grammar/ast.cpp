
#include "y/jive/syntax/node/terminal.hpp"
#include "y/jive/syntax/node/internal.hpp"
#include "y/jive/syntax/grammar.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Syntax
        {


            Node * Grammar:: AST(Node * const node, const size_t depth) noexcept
            {
                assert(0!=node);
                
                return node;
            }

        }

    }

}


