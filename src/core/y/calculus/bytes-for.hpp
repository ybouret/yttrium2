
//! \file

#ifndef Y_Calculus_BytesFor_Included
#define Y_Calculus_BytesFor_Included 1

#include "y/type/ints.hpp"

namespace Yttrium
{
    namespace Calculus
    {
        //______________________________________________________________________
        //
        //
        //
        //! low-level BytesFor computation
        //
        //
        //______________________________________________________________________
        struct BytesFor
        {
            static unsigned Count(const uint8_t  &) noexcept; //!< \return bytes for argument
            static unsigned Count(const uint16_t &) noexcept; //!< \return bytes for argument
            static unsigned Count(const uint32_t &) noexcept; //!< \return bytes for argument
            static unsigned Count(const uint64_t &) noexcept; //!< \return bytes for argument
        };
    }

    //! generic bits for integral argument
    /**
     \param x integrgal value
     \return number of bytes to hold x
     */
    template <typename T> inline
    unsigned BytesFor(const T &x) noexcept
    {
        typedef typename UnsignedIntFor<T>::Result::Type U;
        union  {
            T X;
            U Y;
        } alias = { x };
        return Calculus::BytesFor::Count(alias.Y);
    }
}

#endif

