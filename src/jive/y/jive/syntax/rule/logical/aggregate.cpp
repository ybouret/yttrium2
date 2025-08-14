
#include "y/jive/syntax/rule/logical/aggegate.hpp"
#include "y/jive/syntax/node/internal.hpp"
#include "y/stream/output.hpp"

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
                NodeList branch;

                // check all nodes
                for(const RuleNode *r=(*this)->head;r;r=r->next)
                {
                    const Rule &rule = **r;
                    Node *      node = 0;
                    if(rule.accepts(node,lexer,source))
                    {
                        if(node) branch.pushTail(node);
                        continue;
                    }

                    // failure, return list to lexer
                    Node::Restore(branch,lexer);
                    return false;
                }

                // create node
                InternalNode * node = Node::Make(*this);
                Node::Grow(tree, & node->steal(branch) );
                return true;
            }

            OutputStream & Aggregate:: vizDecl(OutputStream &fp) const
            {
                nodeName(fp) << '[';
                Label(fp,*name);
                fp << ",shape=house";
                return Endl(fp<<']');
            }
        }

    }

}
