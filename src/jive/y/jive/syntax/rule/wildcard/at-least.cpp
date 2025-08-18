

#include "y/jive/syntax/rule/wildcard/at-least.hpp"
#include "y/jive/syntax/node/internal.hpp"
#include "y/system/exception.hpp"
#include "y/stream/output.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {

            AtLeast:: ~AtLeast() noexcept
            {
            }


            bool AtLeast:: accepts(Node * & tree, Lexer &lexer, Source &source, size_t depth) const
            {
                Y_Jive_XRule("[" << name << "]"); ++depth;
                if(0==tree) throw Specific::Exception(name->c_str(),"need a parent rule!!");
                assert(tree->isInternal());
                InternalNode * const target =  dynamic_cast<InternalNode *>(tree); assert(0!=target);


                size_t       count = 0;
                while(true)
                {
                    Node * node = target;
                    const size_t oldCount = target->size;
                    if(rule.accepts(node,lexer,source,depth))
                    {
                        if(target->size<=oldCount)
                            throw Specific::Exception(name->c_str(),"will accept infinite '%s'", rule.name->c_str());
                        ++count;
                    }
                    else
                        break;
                }

                if(count<minCount)
                {
                    --depth; Y_Jive_XRule("[" << name << "]" << Core::Failure << "@" << count);
                    while(count-- > 0)
                        Node::Restore(target->popTail(),lexer);
                    return false;
                }

                

                --depth; Y_Jive_XRule("[" << name << "]" << Core::Success << "@" << count);
                return true;
            }


            ZeroOrMore:: ~ZeroOrMore() noexcept
            {
            }

            OneOrMore:: ~OneOrMore() noexcept
            {
            }


            OutputStream & AtLeast:: vizDecl(OutputStream &fp) const
            {
                nodeName(fp) << '[';
                Label(fp,*name);
                fp << ",shape=oval";
                return Endl(fp<<']');
            }
        }


    }

}

