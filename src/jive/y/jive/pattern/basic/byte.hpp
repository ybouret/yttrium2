
//! \file

#ifndef Y_Pattern_Single_Included
#define Y_Pattern_Single_Included 1

#include "y/jive/pattern.hpp"

namespace Yttrium
{
    namespace Jive
    {

        Y_Jive_Pattern_Decl(Byte,Pattern,'B','Y','T','E'); //!< Enter:: Single
        explicit Byte(const uint8_t)  noexcept;    //!< setup
        explicit Byte(const Byte &) noexcept;    //!< duplicate
        Y_Jive_Pattern_API();

        const uint8_t code;         //!< matching code
        Y_Jive_Pattern_End(Byte); //!< Leave: Single
    }
}

#endif

