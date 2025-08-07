
//! \file

#ifndef Y_Jive_Token_Included
#define Y_Jive_Token_Included 1

#include "y/jive/char.hpp"


namespace Yttrium
{
    namespace Jive
    {
        
        //______________________________________________________________________
        //
        //
        //
        //! List of Chars with unique shared cache
        //
        //
        //______________________________________________________________________
        class Token : public Char::List, public Recyclable
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //______________________________________________________________________
            explicit Token() noexcept;         //!< setup
            virtual ~Token() noexcept;         //!< cleanup
            Token(const Token & );             //!< duplicate
            Y_OSTREAM_PROTO(Token);            //!< display
            
            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            virtual void free() noexcept; //!< free content

            Token & operator<<(const Token &);

        private:
            Y_Disable_Assign(Token); //!< discarding
            void clear() noexcept;   //!< return to pool
        };
    }
}

#endif

