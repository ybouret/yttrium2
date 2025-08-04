
//! \file

#ifndef Y_Pattern_Single_Included
#define Y_Pattern_Single_Included 1

#include "y/jive/pattern.hpp"

namespace Yttrium
{
    namespace Jive
    {

        Y_Jive_Pattern_Decl(Single,Pattern,'S','N','G','L'); //!< Enter:: Single
        explicit Single(const uint8_t)  noexcept;    //!< setup
        explicit Single(const Single &) noexcept;    //!< duplicate
        Y_Jive_Pattern_API();

        const uint8_t code;         //!< matching code
        Y_Jive_Pattern_End(Single); //!< Leave: Single
    }
}

#endif

