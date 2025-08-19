
#include "y/jive/syntax/node/terminal.hpp"
#include "y/jive/syntax/node/internal.hpp"
#include "y/jive/syntax/grammar.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Syntax
        {

            namespace
            {

                static inline
                Node * TerminalAST( TerminalNode * const node, const size_t depth ) noexcept
                {
                    assert(0!=node);
                    const Terminal * const term = dynamic_cast<const Terminal *>( & node->rule );
                    assert(0!=term);

                    if(term->univocal)
                    {
                        node->lexeme->free();
                    }

                    Y_Jive_XRule("Terminal " << *node->lexeme);
                    return node;
                }

                static inline
                void PostProcess(NodeList            &list,
                                 TerminalNode * const node) noexcept
                {
                    assert(0!=node);
                    const Terminal * const term = dynamic_cast<const Terminal *>( & node->rule );
                    assert(0!=term);
                    switch(term->activity)
                    {
                        case Regular: list.pushTail(node); break;
                        case Divider: delete node;         break;
                    }
                }

                static inline
                void MergeAll(NodeList            &list,
                              InternalNode * const node)
                {
                    assert(0!=node);
                    list.mergeTail(*node);
                    delete node;
                }

                static inline
                void ProcessAggregate(NodeList &           list,
                                      InternalNode * const node)
                {
                    assert(0!=node);
                    assert(Aggregate::UUID==node->rule.uuid);
                    const Aggregate * const agg = dynamic_cast<const Aggregate *>( & node->rule );
                    assert(0!=agg);

                    switch(agg->ppty)
                    {
                        case Standard: list.pushTail(node); return;
                        case Grouping: MergeAll(list,node); return;
                        case ActingAs:
                            if(node->size<=1)
                                MergeAll(list,node);
                            else
                                list.pushTail(node);
                            return;
                    }


                }


                static inline
                void PostProcess(NodeList &           list,
                                 InternalNode * const node)
                {
                    assert(0!=node);
                    switch(node->rule.uuid)
                    {
                        case Aggregate::UUID: return ProcessAggregate(list,node);

                        default:
                            break;
                    }
                    list.pushTail(node);
                }


                static inline
                Node * InternalAST( InternalNode * const node, size_t depth) noexcept
                {
                    assert(0!=node);
                    Y_Jive_XRule("Internal [" << node->name() << "]"); ++depth;

                    {
                        NodeList list;
                        while(node->size)
                        {
                            Node * const sub  = Grammar::AST(node->popHead(),depth);

                            switch(sub->type)
                            {
                                case IsTerminal: PostProcess(list, dynamic_cast<TerminalNode *>(sub)); break;
                                case IsInternal: PostProcess(list, dynamic_cast<InternalNode *>(sub)); break;
                            }

                        }
                        node->steal(list);
                    }

                    return node;
                }

            }

            Node * Grammar:: AST(Node * const node, const size_t depth) noexcept
            {
                assert(0!=node);

                switch(node->type)
                {
                    case  IsTerminal: return TerminalAST( dynamic_cast<TerminalNode*>(node), depth );
                    case  IsInternal: return InternalAST( dynamic_cast<InternalNode*>(node), depth );
                }

                return node;
            }

        }

    }

}


