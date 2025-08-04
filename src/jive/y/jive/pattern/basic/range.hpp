

//! \file

#ifndef Y_Pattern_Range_Included
#define Y_Pattern_Range_Included 1

#include "y/jive/pattern.hpp"

namespace Yttrium
{
    namespace Jive
    {

        Y_Jive_Pattern_Decl(Range,'R','N','G','E');

        explicit Range(const uint8_t, const uint8_t ) noexcept;
        explicit Range(const Range &)                 noexcept;
        Y_Jive_Pattern_API();

        const uint8_t lower;
        const uint8_t upper;

        Y_Jive_Pattern_End(Range);
    }
}

#endif

