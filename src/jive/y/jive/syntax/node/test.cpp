
#include "y/jive/syntax/node/internal.hpp"
#include "y/jive/syntax/node/terminal.hpp"

namespace Yttrium
{

    namespace Jive
    {

        namespace Syntax
        {

            static inline
            bool AreSameTerminal(const Node * const lhs, const Node * const rhs) noexcept
            {
                assert(lhs); assert(lhs);
                assert(lhs->isTerminal()); assert(lhs->isTerminal());

                if(lhs->name()!=rhs->name()) return false;

                const TerminalNode * const L = dynamic_cast<const TerminalNode *>(lhs); assert(L);
                const TerminalNode * const R = dynamic_cast<const TerminalNode *>(rhs); assert(R);

                const Token &lhsToken = *L->lexeme;
                const Token &rhsToken = *R->lexeme;

                return lhsToken == rhsToken;
            }

            static inline
            bool AreSameInternal(const Node * const lhs, const Node * const rhs) noexcept
            {
                assert(lhs); assert(lhs);
                assert(lhs->isInternal());
                assert(lhs->isInternal());

                if(lhs->name()!=rhs->name()) return false;

                const InternalNode * const L = dynamic_cast<const InternalNode *>(lhs); assert(L);
                const InternalNode * const R = dynamic_cast<const InternalNode *>(rhs); assert(R);

                if(L->size!=R->size) return false;

                for(const Node *l = L->head, *r = R->head; l; l=l->next, r=r->next)
                {
                    assert(l);
                    assert(r);
                    if( ! Node::AreEqual(l,r) ) return false;
                }


                return true;
            }



            bool Node:: AreEqual(const Node *const lhs, const Node *const rhs) noexcept
            {
                assert(lhs); assert(lhs);

                static const unsigned LT = 0x01;
                static const unsigned LI = 0x02;
                static const unsigned RT = 0x04;
                static const unsigned RI = 0x08;

                unsigned flag = 0x00;
                switch(lhs->type)
                {
                    case IsInternal: flag |= LI; break;
                    case IsTerminal: flag |= LT; break;
                }

                switch(rhs->type)
                {
                    case IsInternal: flag |= RI; break;
                    case IsTerminal: flag |= RT; break;
                }

                switch(flag)
                {
                    case LT|RT: return AreSameTerminal(lhs,rhs);
                    case LI|RI: return AreSameInternal(lhs,rhs);
                    default:
                        break;
                }

                return false;

            }
        }

    }

}
