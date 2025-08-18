
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
                Y_Jive_XRule("[ [?] Agg '" << name << "']"); ++depth;

                InternalNode * const  self = Node::Make(*this);
                AutoPtr<Node>         keep(self);
                Node *                node = self;

                // check all nodes
                for(const RuleNode *r=(*this)->head;r;r=r->next)
                {
                    const Rule &rule = **r;
                    if(rule.accepts(node,lexer,source,depth))
                    {
                        continue;
                    }

                    // failure, return list to lexer
                    Node::Restore(keep.yield(),lexer);
                    --depth; Y_Jive_XRule("[ [-] Agg '" << name << "']");
                    return false;
                }

                // create node
                Node::Grow(tree, keep.yield() );
                --depth; Y_Jive_XRule("[ [+] Agg '" << name << "']");
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
