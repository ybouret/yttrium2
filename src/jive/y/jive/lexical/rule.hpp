
//! \file

#ifndef Y_Jive_Lexical_Rule_Included
#define Y_Jive_Lexical_Rule_Included 1

#include "y/jive/token.hpp"
#include "y/jive/pattern.hpp"

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
            //! Rule = name + motif + flags
            //
            //
            //__________________________________________________________________
            class Rule : public Object
            {
            public:
                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                Rule(const Tag &, const Motif &) noexcept; //!< setup
                Rule(const Rule &)               noexcept; //!< duplicate
                virtual ~Rule()                  noexcept; //!< cleanup

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const Tag   name;  //!< name
                const Motif motif; //!< motif to match
                Rule *      next;  //!< for list
                Rule *      prev;  //!< for list

            private:
                Y_Disable_Assign(Rule); //!< discarding
            };
        }
    }

}

#endif

