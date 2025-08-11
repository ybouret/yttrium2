//! \file


#ifndef Y_Jive_Syntax_Node_Included
#define Y_Jive_Syntax_Node_Included 1

#include "y/jive/lexer.hpp"
#include "y/jive/syntax/category.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Syntax
        {

            class   Rule;
            class   Internal;
            class   Terminal;
            class   Node;
            typedef CxxListOf<Node> NodeList;
            class   InternalNode;
            class   TerminalNode;

            class Node : public Object, public Vizible
            {
            protected:
                explicit Node(const Category, const Rule &) noexcept;
            public:
                virtual ~Node() noexcept;


                static  void Restore(Node * const, Lexer &) noexcept;
                virtual void restore(Lexer &) noexcept = 0;

                static TerminalNode * Make(const Terminal &, Lexeme * const);
                static InternalNode * Make(const Internal &);


                const Category       type;
                const Rule          &rule;
                InternalNode * const sire;
                Node *               next;
                Node *               prev;

            private:
                Y_Disable_Copy_And_Assign(Node);
            };


            
        }

    }
}


#endif

