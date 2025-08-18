

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
                NodeList list;
                size_t   n_ok = 0;

                while(true)
                {
                    Node * node = 0;
                    if(rule.accepts(node,lexer,source,depth))
                    {
                        if(0==node)
                            throw Specific::Exception(name->c_str(),"will accept infinite '%s'", rule.name->c_str());
                        ++n_ok;
                        list.pushTail(node);
                    }
                    else
                        break;
                }

                if(n_ok<minCount)
                {
                    Node::Restore(list,lexer);
                    --depth; Y_Jive_XRule("[" << name << "]" << Core::Failure << "@" << n_ok);
                    return false;
                }


                if(tree)
                {
                    assert(tree->isInternal());
                    dynamic_cast<InternalNode *>(tree)->steal(list);
                }
                else
                {
                    // bad grammar, but...
                    InternalNode * const node = Node::Make(*this);
                    node->steal(list);
                    tree = node;
                }
                --depth; Y_Jive_XRule("[" << name << "]" << Core::Success << "@" << n_ok);
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

