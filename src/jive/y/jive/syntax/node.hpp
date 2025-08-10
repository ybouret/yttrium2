//! \file


#ifndef Y_Jive_Syntax_Node_Included
#define Y_Jive_Syntax_Node_Included 1

#include "y/jive/lexer.hpp"
#include "y/calculus/alignment.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Syntax
        {

            enum Category
            {
                IsTerminal,
                IsInternal
            };

            class   Node;
            typedef CxxListOf<Node> NodeList;
            class   InternalNode;
            class   TerminalNode;

            class Node : public Object, public Vizible
            {
            protected:
                explicit Node(const Category, InternalNode * const) noexcept;
            public:
                virtual ~Node() noexcept;


                virtual void restore(Lexer &) noexcept = 0;

                TerminalNode * Make(InternalNode * const, Lexeme * const);
                InternalNode * Make(InternalNode * const);


                const Category       type;
                InternalNode * const sire;
                Node *               next;
                Node *               prev;
            private:
                Y_Disable_Copy_And_Assign(Node);
            };



            class TerminalNode : public Node
            {
            public:
                virtual ~TerminalNode() noexcept;

                virtual void restore(Lexer &) noexcept;

                Lexeme * const lexeme;

            private:
                explicit TerminalNode( InternalNode * const, Lexeme * const) noexcept;
                Y_Disable_Copy_And_Assign(TerminalNode);
                friend class Node;

            };



            class InternalNode : public Node, public NodeList
            {
            public:
                virtual ~InternalNode() noexcept;

                virtual void restore(Lexer &) noexcept;

            private:
                Y_Disable_Copy_And_Assign(InternalNode);
                explicit InternalNode(InternalNode * const) noexcept;
                friend class Node;
            };

        }

    }
}


#endif

