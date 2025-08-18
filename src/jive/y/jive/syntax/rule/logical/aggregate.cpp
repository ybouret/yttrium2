
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
                                     Source &source,
                                     size_t  depth) const
            {
                Y_Jive_XRule("[Agg '" << name << "']"); ++depth;

                // local list of aggregated node
                NodeList branch;

                // check all nodes
                for(const RuleNode *r=(*this)->head;r;r=r->next)
                {
                    const Rule &rule = **r;
                    Node *      node = 0;
                    if(rule.accepts(node,lexer,source,depth))
                    {
                        if(node) branch.pushTail(node);
                        continue;
                    }

                    // failure, return list to lexer
                    Node::Restore(branch,lexer);
                    Y_Jive_XRule(Core::Failure);
                    return false;
                }

                // create node
                InternalNode * node = Node::Make(*this);
                Node::Grow(tree, & node->steal(branch) );
                Y_Jive_XRule(Core::Success);
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
