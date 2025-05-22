//! \file

#ifndef Y_Type_Sign_Included
#define Y_Type_Sign_Included 1

#include "y/system/compiler.hpp"

namespace Yttrium
{

    enum SignType
    {
        Negative = -1,
        __Zero__ = 0,
        Positive = 1
    };

    struct Sign
    {
        static const char * HumanReadable(const SignType) noexcept;
    };
}

#endif

