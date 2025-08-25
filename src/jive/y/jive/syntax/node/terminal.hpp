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
            //__________________________________________________________________
            //
            //
            //
            //! Terminal node, with Terminal rule and its lexeme
            //
            //
            //__________________________________________________________________
            class TerminalNode : public Node
            {
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
            private:
                //! setup with rule and lexeme != 0
                explicit TerminalNode(const Terminal &,
                                      Lexeme * const) noexcept;

            public:
                virtual ~TerminalNode() noexcept; //!< cleanup

                //______________________________________________________________
                //
                //
                // Interface
                //
                //______________________________________________________________
                virtual OutputStream &       viz(OutputStream &)       const;
                virtual const TerminalNode * lastTerm()       const noexcept;
                virtual size_t               serialize(OutputStream &) const;
                virtual Node               * clone()                   const;

                //______________________________________________________________
                //
                //
                // Methods
                //
                //______________________________________________________________
                String str() const; //!< \return string with or w/o content

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                Lexeme * const  lexeme; //!< lexeme, NULL once returned to Lexer
                
            private:
                Y_Disable_Copy_And_Assign(TerminalNode); //!< discarding
                friend class Node;
                virtual void restore(Lexer &) noexcept;
                String       lex2str() const; //!< \return empty if univocal
            };
        }

    }

}

#endif

