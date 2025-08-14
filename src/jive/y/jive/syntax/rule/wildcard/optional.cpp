
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

            bool Optional:: accepts(Node * & tree, Lexer &lexer, Source &source) const
            {
                Node * node = 0;
                
                if(rule.accepts(node,lexer,source))
                {
                    if(node)
                    {
                        Node::Grow(tree,node);
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

