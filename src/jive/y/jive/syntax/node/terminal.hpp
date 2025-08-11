//! \file

#ifndef Y_Jive_Syntax_TerminalNode_Included
#define Y_Jive_Syntax_TerminalNode_Included 1

#include "y/jive/syntax/node.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Syntax
        {
            //! TerminalNode a.k.a lexeme smart pointer
            class TerminalNode : public Node
            {
            public:
                virtual ~TerminalNode() noexcept;

                Lexeme * const lexeme;

            private:
                explicit TerminalNode(const Terminal &, Lexeme * const) noexcept;
                Y_Disable_Copy_And_Assign(TerminalNode);
                friend class Node;
                virtual void restore(Lexer &) noexcept;
            };
        }

    }

}

#endif

