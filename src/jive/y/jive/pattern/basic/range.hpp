

//! \file

#ifndef Y_Pattern_Range_Included
#define Y_Pattern_Range_Included 1

#include "y/jive/pattern.hpp"

namespace Yttrium
{
    namespace Jive
    {

        Y_Jive_Pattern_Decl(Range,Pattern,'R','N','G','E'); //!< Enter: Range
        explicit Range(const uint8_t, const uint8_t ) noexcept; //!< setup
        explicit Range(const Range &)                 noexcept; //!< duplicate
        Y_Jive_Pattern_API();  //!< API

        const uint8_t lower; //!< lower code
        const uint8_t upper; //!< upper code

        Y_Jive_Pattern_End(Range); //!< Leave: Range
    }
}

#endif

