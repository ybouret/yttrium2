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

                Y_Jive_XRule("[ [?] Alt " << name << "]"); ++depth;

                for(const RuleNode *r=(*this)->head;r;r=r->next)
                {
                    const Rule &rule = **r;
                    if(rule.accepts(tree,lexer,source,depth))
                    {
                        --depth; Y_Jive_XRule("[ [+] Alt " << name << "] @" << rule.name);
                        return true;
                    }
                }
                --depth; Y_Jive_XRule("[ [-] Alt " << name << "]");
                return false;
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
