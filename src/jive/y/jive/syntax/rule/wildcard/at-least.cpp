

#include "y/jive/syntax/rule/wildcard/at-least.hpp"
#include "y/jive/syntax/node/internal.hpp"
#include "y/system/exception.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Syntax
        {

            AtLeast:: ~AtLeast() noexcept
            {
            }

            bool AtLeast:: accepts(Node * & tree, Lexer &lexer, Source &source) const
            {
                NodeList list;
                size_t   n_ok = 0;

                while(true)
                {
                    Node * node = 0;
                    if(rule.accepts(node,lexer,source))
                    {
                        if(0==node)
                            throw Specific::Exception(name->c_str(),"will accept infinite '%s'", rule.name->c_str());
                        ++n_ok;
                        list.pushTail(node);
                    }
                }

                if(n_ok<minCount)
                {
                    while(list.size)
                        Node::Restore(list.popTail(),lexer);
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

                return true;
            }


            ZeroOrMore:: ~ZeroOrMore() noexcept
            {
            }

            OneOrMore:: ~OneOrMore() noexcept
            {
            }

        }


    }

}

