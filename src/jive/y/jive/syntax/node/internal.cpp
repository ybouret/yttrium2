#include "y/jive/syntax/node/internal.hpp"
#include "y/jive/syntax/rule/internal.hpp"
namespace Yttrium
{

    namespace Jive
    {

        namespace Syntax
        {

            InternalNode:: ~InternalNode() noexcept
            {
            }

            InternalNode:: InternalNode(const Internal &r) noexcept:
            Node(IsInternal,r)
            {
            }

            InternalNode * Node::Make(const Internal &r)
            {
                return new InternalNode(r);
            }

            void InternalNode:: restore(Lexer &lexer) noexcept
            {
                Restore(*this,lexer);
            }

            InternalNode & InternalNode :: operator<<(Node * const node)
            {
                return * ( Coerce(pushTail(node)->sire) = this );
            }

            InternalNode & InternalNode:: steal(NodeList &list) noexcept
            {
                while(list.size>0) *this << list.popHead();
                return *this;
            }

        }
    }

}

