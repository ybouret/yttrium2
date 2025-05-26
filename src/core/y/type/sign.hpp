//! \file

#ifndef Y_Type_Sign_Included
#define Y_Type_Sign_Included 1

#include "y/core/setup.hpp"
#include <cassert>

namespace Yttrium
{

    //! Named Sign
    enum SignType
    {
        Negative = -1, //!< named negative value
        __Zero__ =  0, //!< named zero value
        Positive =  1  //!< named positive value
    };


    //! operations on signs
    struct Sign
    {
        static const char * HumanReadable(const SignType)     noexcept; //!< named value \return C string
        static bool         StriclyIncreasing(const SignType) noexcept; //!< check \return true for Negative
        static bool         LooselyIncreasing(const SignType) noexcept; //!< check \return true for Negative|__Zero__
        static bool         StriclyDecreasing(const SignType) noexcept; //!< check \return true for Positive
        static bool         LooselyDecreasing(const SignType) noexcept; //!< check \return true for Positive|__Zero__


        //! natural sign
        template <typename T> static inline
        SignType Of(const T &value)
        {
            return value<0 ? Negative : (0<value ? Positive : __Zero__ );
        }

        //! natural comparison
        /**
         \param lhs lhs
         \param rhs rhs
         \return sign relying on '<' operator
         */
        template <typename T> static inline
        SignType Of(const T &lhs, const T &rhs)
        {
            return (lhs < rhs) ? Negative : ( (rhs<lhs) ? Positive : __Zero__ );
        }

        //! C-style natural comparison for qsort etc...
        /**
         \param lhs address of left object
         \param rhs address of right object
         \return integer comparison
         */
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

