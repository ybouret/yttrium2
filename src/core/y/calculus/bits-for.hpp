
//! \file

#ifndef Y_Calculus_BitsFor_Included
#define Y_Calculus_BitsFor_Included 1

#include "y/type/ints.hpp"

namespace Yttrium
{
    namespace Calculus
    {
        //______________________________________________________________________
        //
        //
        //
        //! low-level BitsFor computation
        //
        //
        //______________________________________________________________________
        struct BitsFor
        {
            static const unsigned Table[256];                 //!< precomputed for uint8_t
            static unsigned Count(const uint8_t  &) noexcept; //!< \return bits for argument
            static unsigned Count(const uint16_t &) noexcept; //!< \return bits for argument
            static unsigned Count(const uint32_t &) noexcept; //!< \return bits for argument
            static unsigned Count(const uint64_t &) noexcept; //!< \return bits for argument
        };
    }

    //! generic bits for integral argument
    /**
     \param x integrgal value
     \return number of bits to hold x
     */
    template <typename T> inline
    unsigned BitsFor(const T &x) noexcept
    {
        typedef typename UnsignedIntFor<T>::Result::Type U;
        union  {
            T X;
            U Y;
        } alias = { x };
        return Calculus::BitsFor::Count(alias.Y);
    }


}

#endif // !Y_Calculus_BitsFor_Included

