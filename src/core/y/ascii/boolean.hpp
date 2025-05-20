
//! \file

#ifndef Y_ASCII_Boolean_Included
#define Y_ASCII_Boolean_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{

    namespace ASCII
    {
        struct Boolean
        {
            static const char *Text(const bool flag) noexcept;
            static const char *text(const bool flag) noexcept;

        };
    }

}

#endif

