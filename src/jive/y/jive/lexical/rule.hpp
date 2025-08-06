
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
                Drop,
                Call,
                Back
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
            /**
             - EOF
             - standard: emit/drop
             - control:  jump/back
             */
            //
            //__________________________________________________________________
            class Rule : public Object
            {
            public:
                //______________________________________________________________
                //
                //
                // Definitions
                //
                //______________________________________________________________
                typedef CxxListOf<Rule> List; //!< alias
                
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
                const Attribute attr;  //!< attribute
                const Demeanor  deed;  //!< demeanor
                Rule *          next;  //!< for list
                Rule *          prev;  //!< for list
            private:
                Y_Disable_Copy_And_Assign(Rule); //!< discarding
            };
        }
    }

}

#endif

