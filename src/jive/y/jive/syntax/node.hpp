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
            class   InternalNode;
            class   TerminalNode;
            typedef CxxListOf<Node> NodeList; //!< alias


            //__________________________________________________________________
            //
            //
            //
            //! base class for Nodes
            //
            //
            //__________________________________________________________________
            class Node : public Object, public Vizible
            {
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
            protected:
                //! setup
                explicit Node(const Category, const Rule &) noexcept;

            public:
                // cleanup
                virtual ~Node() noexcept;

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                virtual void           restore(Lexer &)    noexcept = 0; //!< restore content
                virtual OutputStream & viz(OutputStream &) const    = 0; //!< emit GraphViz code \return output stream

                //______________________________________________________________
                //
                //
                // Helpers
                //
                //______________________________________________________________

                //! restore content to lexer and delete node
                static  void Restore(Node * const, Lexer &) noexcept;

                //! restore list to lexer
                static  void Restore(NodeList &, Lexer &) noexcept;

                //! \return new terminal node from Terminal Rule
                static TerminalNode * Make(const Terminal &, Lexeme * const);

                //! \return new internal node Internal Rule (TODO: aggregate)
                static InternalNode * Make(const Internal &);

                //! grow a tree with a new node
                static void Grow(Node * &, Node * const) noexcept;

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________
                bool isInternal() const noexcept; //!< \return type == IsInternal
                bool isTerminal() const noexcept; //!< \return type == IsTerminal

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const Category       type; //!< category
                const Rule          &rule; //!< accepting rule
                InternalNode * const sire; //!< parent list if any
                Node *               next; //!< for list
                Node *               prev; //!< for list

            private:
                Y_Disable_Copy_And_Assign(Node); //!< discarding
            };


            
        }

    }
}


#endif

