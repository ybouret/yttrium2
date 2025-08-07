
//! \file

#ifndef Y_Jive_Lexical_Design_Included
#define Y_Jive_Lexical_Design_Included 1

#include "y/jive/lexical/no-data.hpp"
#include "y/jive/pattern/dictionary.hpp"

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
            //! common resources to design scanners
            //
            //
            //__________________________________________________________________
            class Design
            {
            public:
                explicit Design();                        //!< new dictionary and noData
                explicit Design(const Design &) noexcept; //!< duplicate
                virtual ~Design() noexcept;               //!< cleanup

                const Dictionary::Pointer pdb; //!< shared dictionary
                const NoData              nil; //!< empty nil.tag

            private:
                Y_Disable_Assign(Design); //!< discarding
            };
        }

    }

}

#endif
