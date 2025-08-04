
//! \file

#ifndef Y_Pattern_Single_Included
#define Y_Pattern_Single_Included 1

#include "y/jive/pattern.hpp"

namespace Yttrium
{
    namespace Jive
    {

        Y_Jive_Pattern_Decl(Single,'S','N','G','L');

        explicit Single(const uint8_t)  noexcept;
        explicit Single(const Single &) noexcept;
        Y_Jive_Pattern_API();

        const uint8_t code;

        Y_Jive_Pattern_End(Single);
    }
}

#endif

