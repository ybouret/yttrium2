
#include "y/jive/syntax/node/terminal.hpp"
#include "y/jive/syntax/node/internal.hpp"
#include "y/jive/syntax/grammar.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Syntax
        {

            static inline
            Node * InternalAST(InternalNode * const node) noexcept
            {
                {
                    NodeList temp;
                    while(node->size)
                    {
                        Node * const sub = Grammar::AST( node->popHead() );
                        if(sub) temp.pushTail(sub);
                    }
                    node->steal(temp);
                }
                return node;
            }

            static inline
            Node * TerminalAST(TerminalNode * const node) noexcept
            {
                assert(0!=node);
                const Terminal &rule = dynamic_cast<const Terminal&>(node->rule);

                switch(rule.activity)
                {
                    case Divider: delete node; return 0;
                    case Regular:
                        break;
                }

                if(rule.univocal) node->lexeme->free();
                return node;
            }

            Node * Grammar:: AST(Node * const node) noexcept
            {
                assert(0!=node);
                switch(node->type)
                {
                    case IsTerminal: return TerminalAST( dynamic_cast<TerminalNode *>(node) );
                    case IsInternal: return InternalAST( dynamic_cast<InternalNode *>(node) );
                }
                return node;
            }

        }

    }

}


