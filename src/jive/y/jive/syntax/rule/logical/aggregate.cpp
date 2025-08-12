
#include "y/jive/syntax/rule/logical/aggegate.hpp"
#include "y/jive/syntax/node/internal.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {

            Aggregate:: ~Aggregate() noexcept
            {
            }


            bool Aggregate:: accepts(Node * &tree,
                                     Lexer  &lexer,
                                     Source &source) const
            {
                // local list of aggregated node
                NodeList list;

                // check all nodes
                for(const RuleNode *r=(*this)->head;r;r=r->next)
                {
                    const Rule &rule = **r;
                    Node *      node = 0;
                    if(rule.accepts(node,lexer,source))
                    {
                        if(node) list.pushTail(node);
                        continue;
                    }

                    // failure, return list to lexer
                    while(list.size)
                        Node::Restore(list.popTail(),lexer);
                    return false;
                }

                // create node
                InternalNode * node = Node::Make(*this);
                node->swapListFor(list);
                Node::Grow(tree,node);
                return true;
            }
        }

    }

}
