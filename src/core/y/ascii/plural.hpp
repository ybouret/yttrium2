

//! \file

#ifndef Y_ASCII_Plural_Included
#define Y_ASCII_Plural_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{

    namespace ASCII
    {
        //! plural if needed
        struct Plural
        {
            static const char * s(const size_t) noexcept;
            static const char * S(const size_t) noexcept;
        };

    }

}

#endif
