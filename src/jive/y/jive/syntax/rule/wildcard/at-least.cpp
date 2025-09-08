

#include "y/jive/syntax/rule/wildcard/at-least.hpp"
#include "y/jive/syntax/node/internal.hpp"
#include "y/exception.hpp"
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

                InternalNode * const self  = Node::Make(*this);
                Node         *       goal  = self;
                AutoPtr<Node>        keep  = goal;
                size_t               count = 0;

                while(true)
                {
                    size_t oldSize = self->size;
                    if(rule.accepts(goal, lexer, source, depth))
                    {
                        if(self->size<=oldSize)
                            throw Specific::Exception(name->c_str(),"infinity of '%s'", rule.name->c_str());
                        ++count;
                    }
                    else
                        break;
                }

                --depth;

                if(count<minCount)
                {
                    Y_Jive_XRule("[" << name << "] " << Core::Failure << "@" << count << "<" << minCount);
                    Node::Restore(keep.yield(),lexer);
                    return false;
                }
                else
                {
                    Y_Jive_XRule("[" << name << "] " << Core::Success << "@" << count << ">=" << minCount);
                    if(!tree)
                    {
                        tree = keep.yield();
                    }
                    else
                    {
                        assert(tree->isInternal());
                        InternalNode * const target = dynamic_cast<InternalNode *>(tree); assert(target);
                        target->steal(*self);
                    }
                    return true;
                }

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

