
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
                (void) rule.accepts(tree,lexer,source,depth);
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

