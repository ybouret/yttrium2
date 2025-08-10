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
            typedef CxxListOf<Node> XList;

            class Node : public Object, public Vizible
            {
            public:
                static const unsigned   ListWords = Alignment::WordsFor<XList>::Count;


                virtual ~Node() noexcept;

                Node * Make(Lexeme * const lx);
                Node * Make();

                Lexeme &       lexeme() noexcept;
                const Lexeme & lexeme() const noexcept;

                const Category type;
                Node * const   sire;
            private:
                Y_Disable_Copy_And_Assign(Node);
                explicit Node(Lexeme * const lx) noexcept;
                explicit Node() noexcept;
                void * const data;
                void *wksp[ListWords];

                Lexeme * queryLexeme() const noexcept;
                XList  & returnXList() const noexcept;

            public:
                Node *       next;
                Node *       prev;

            };

        }

    }
}


#endif

