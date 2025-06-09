
//! \file

#ifndef Y_Calculus_BitsFor_Included
#define Y_Calculus_BitsFor_Included 1

#include "y/type/ints.hpp"

namespace Yttrium
{
    namespace Calculus
    {
        struct BitsFor
        {
            static const unsigned Table[256];
            static unsigned Count(const uint8_t  &) noexcept;
            static unsigned Count(const uint16_t &) noexcept;
            static unsigned Count(const uint32_t &) noexcept;
            static unsigned Count(const uint64_t &) noexcept;
        };
    }

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

#endif

