#include "y/jive/syntax/node/internal.hpp"
#include "y/jive/syntax/rule/internal.hpp"
#include "y/stream/output.hpp"

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

            OutputStream & InternalNode:: viz(OutputStream &fp) const
            {
                nodeName(fp) << '[';
                Label(fp,*rule.name);
                Endl( fp << ']');

                const bool show = size>1;
                unsigned   indx = 1;
                for(const Node * node=head;node;node=node->next,++indx)
                {
                    assert(this==node->sire);
                    to( node, node->viz(fp) );
                    if(show) fp("[label=\"%u\"]",indx);
                    Endl(fp);
                }


                return fp;
            }

            const Terminal * InternalNode:: lastTerm()    const noexcept
            {
                if(size<=0) return 0;
                return tail->lastTerm();
            }

        }
    }

}

