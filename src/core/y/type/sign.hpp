//! \file

#ifndef Y_Type_Sign_Included
#define Y_Type_Sign_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{

    enum SignType
    {
        Negative = -1,
        __Zero__ =  0,
        Positive =  1
    };

    struct Sign
    {
        static const char * HumanReadable(const SignType) noexcept;
        static bool         StriclyIncreasing(const SignType) noexcept;
        static bool         LooselyIncreasing(const SignType) noexcept;
        static bool         StriclyDecreasing(const SignType) noexcept;
        static bool         LooselyDecreasing(const SignType) noexcept;

    };
}

#endif

