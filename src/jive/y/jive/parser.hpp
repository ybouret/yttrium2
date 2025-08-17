//! \file


#ifndef Y_Jive_Parser_Included
#define Y_Jive_Parser_Included 1

#include "y/jive/syntax/grammar.hpp"


namespace Yttrium
{
    namespace Jive
    {

        //______________________________________________________________________
        //
        //
        //
        //! Parser = Lexer + Grammar
        //
        //
        //______________________________________________________________________
        class Parser : public Lexer, public Syntax::Grammar
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup \param id name and lang
            template <typename ID> inline
            explicit Parser(const ID &id) :
            Lexer(id), Syntax::Grammar(name,this)
            {
            }

            


            //! cleanup
            virtual ~Parser() noexcept;

        private:
            Y_Disable_Copy_And_Assign(Parser); //!< discarding
        };
    }

}

#endif

