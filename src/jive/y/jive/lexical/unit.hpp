
//! \file

#ifndef Y_Jive_Lexical_Unit_Included
#define Y_Jive_Lexical_Unit_Included 1

#include "y/jive/token.hpp"
#include "y/core/linked/list/cxx.hpp"

namespace Yttrium
{
    namespace Jive
    {

        namespace Lexical
        {

            //__________________________________________________________________
            //
            //
            //
            //! Unit = named and located token
            //
            //
            //__________________________________________________________________
            class Unit : public Object, public Context, public Token
            {
            public:
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                Unit(const Tag &, const Context &) noexcept; //!< cleanup
                Unit(const Unit &);                          //!< duplicate
                virtual ~Unit() noexcept;                    //!< cleanup
                Y_OSTREAM_PROTO(Unit);

                const Unit & operator*() const noexcept { return *this; }

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const Tag name; //!< name
                Unit *    next; //!< for list
                Unit *    prev; //!< for list

            private:
                Y_Disable_Assign(Unit); //!< discarding
            };

        }

        typedef Lexical::Unit     Lexeme;
        typedef CxxListOf<Lexeme> Lexemes;
    }

}

#endif
