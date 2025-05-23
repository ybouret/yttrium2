//! \file

#ifndef Y_Type_Sign_Included
#define Y_Type_Sign_Included 1

#include "y/core/setup.hpp"
#include <cassert>

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

        //! natural comparison
        template <typename T> static inline
        SignType Of(const T &lhs, const T &rhs)
        {
            return (lhs < rhs) ? Negative : ( (rhs<lhs) ? Positive : __Zero__ );
        }

        //! C-style
        template <typename T> static inline
        int Compare(const void * const lhs, const void * const rhs) noexcept
        {
            assert(0!=lhs);
            assert(0!=rhs);
            return int(Of(*static_cast<const T *>(lhs),*static_cast<const T *>(rhs)));
        }

    };
}

#endif

