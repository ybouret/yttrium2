
//! \file

#ifndef Y_Jive_Lexical_Rule_Included
#define Y_Jive_Lexical_Rule_Included 1

#include "y/jive/token.hpp"
#include "y/jive/pattern.hpp"
#include "y/core/linked/list/cxx.hpp"

namespace Yttrium
{
    namespace Jive
    {
        namespace Lexical
        {

            enum Demeanor
            {
                Emit,
                Drop
            };

            enum Attribute
            {
                Regular,
                NewLine
            };



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
                typedef CxxListOf<Rule> List;



                //______________________________________________________________
                //
                //
                // C++
                //
                //______________________________________________________________
                Rule(const Tag       &,
                     const Motif     &,
                     const Attribute,
                     const bool)  noexcept; //!< setup
                virtual ~Rule()   noexcept; //!< cleanup

                //______________________________________________________________
                //
                //
                // Members
                //
                //______________________________________________________________
                const Tag       name;  //!< name
                const Motif     motif; //!< motif to match
                const Attribute attr;
                const Demeanor  deed;
                Rule *          next;  //!< for list
                Rule *          prev;  //!< for list
            private:
                Y_Disable_Copy_And_Assign(Rule); //!< discarding
            };
        }
    }

}

#endif

