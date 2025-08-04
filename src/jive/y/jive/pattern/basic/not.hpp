

//! \file

#ifndef Y_Pattern_Not_Included
#define Y_Pattern_Not_Included 1

#include "y/jive/pattern.hpp"

namespace Yttrium
{
    namespace Jive
    {

        Y_Jive_Pattern_Decl(Not,Pattern,'_','N','O','T'); //!< Enter:: Not
        explicit Not(const uint8_t)  noexcept;    //!< setup
        explicit Not(const Not &)    noexcept;    //!< duplicate
        Y_Jive_Pattern_API();

        const uint8_t code;      //!< matching code
        Y_Jive_Pattern_End(Not); //!< Leave: Not
    }
}

#endif

