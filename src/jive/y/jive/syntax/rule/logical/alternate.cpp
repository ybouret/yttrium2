

#include "y/jive/syntax/rule/logical/alternate.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {

            Alternate:: ~Alternate() noexcept
            {
            }

            bool Alternate:: accepts(Node * &tree,
                                     Lexer  &lexer,
                                     Source &source) const
            {

                bool accepted = false;

                // check all nodes
                for(const RuleNode *r=(*this)->head;r;r=r->next)
                {
                    const Rule &rule = **r;
                    Node *      node = 0;
                    if(rule.accepts(node,lexer,source))
                    {
                        if(node) {
                            Node::Grow(tree,node);
                            return true;
                        }
                        accepted = true; // give a chance
                    }
                }

                return accepted;
            }
        }

    }

}
