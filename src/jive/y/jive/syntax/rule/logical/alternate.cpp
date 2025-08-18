#include "y/jive/syntax/rule/logical/alternate.hpp"
#include "y/stream/output.hpp"

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
                                     Source &source,
                                     size_t  depth) const
            {

                Y_Jive_XRule("[Alt '" << name << "']"); ++depth;
                bool accepted = false;

                // check one node
                for(const RuleNode *r=(*this)->head;r;r=r->next)
                {
                    const Rule &rule = **r;
                    Node *      node = 0;
                    if(rule.accepts(node,lexer,source,depth))
                    {
                        if(node) {
                            Node::Grow(tree,node);
                            std::cerr << "ok" << std::endl;
                            return true;
                        }
                        accepted = true; // give a chance
                    }
                }

                return accepted;
            }

            OutputStream & Alternate:: vizDecl(OutputStream &fp) const
            {
                nodeName(fp) << '[';
                Label(fp,*name);
                fp << ",shape=egg";
                return Endl(fp<<']');
            }


        }

    }

}
