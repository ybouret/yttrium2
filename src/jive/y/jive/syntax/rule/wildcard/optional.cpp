
#include "y/jive/syntax/rule/wildcard/optional.hpp"
#include "y/stream/output.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {

            Optional:: ~Optional() noexcept
            {
            }

            bool Optional:: accepts(Node * & tree, Lexer &lexer, Source &source, size_t depth) const
            {
                Y_Jive_XRule("[" << name << "]"); ++depth;
                Node * node = 0;
                
                if(rule.accepts(node,lexer,source,depth))
                {
                    if(node)
                    {
                        Node::Grow(tree,node);
                        --depth; Y_Jive_XRule("(not empty)");
                    }
                }

                return true;
            }

            OutputStream & Optional:: vizDecl(OutputStream &fp) const
            {
                nodeName(fp) << '[';
                Label(fp,*name);
                fp << ",shape=diamond";
                return Endl(fp<<']');
            }

        }

    }

}

