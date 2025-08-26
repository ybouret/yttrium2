
//! \file

#ifndef Y_Jive_Token_Included
#define Y_Jive_Token_Included 1

#include "y/jive/char.hpp"
#include "y/apex/natural.hpp"

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
        class Token :
        public Char::List,
        public Recyclable,
        public Serializable
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
            Y_OSTREAM_PROTO(Token);            //!< pretty display

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void   free()                 noexcept; //!< free content
            virtual size_t serialize(OutputStream &) const;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            Token & skip() noexcept; //!< remove head \return *this
            Token & trim() noexcept; //!< remove tail \return *this

            //! convert to raw string
            /**
             \param nskip optional skip count
             \param ntrim optional trim count
             \return raw string
             */
            String toString(const size_t nskip=0, const size_t ntrim=0) const;

            //! \return converted to natural
            apn toNatural() const;

            //! \return true if same content
            friend bool operator==(const Token &, const Token &) noexcept;

        private:
            Y_Disable_Assign(Token); //!< discarding
            void clear() noexcept;   //!< return to pool
        };
    }
}

#endif

