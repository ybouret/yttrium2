
//! \file

#ifndef Y_Color_Conversion_Included
#define Y_Color_Conversion_Included

#include "y/color/conv.hpp"
#include "y/color/rgba.hpp"

namespace Yttrium
{

    namespace Color
    {

        struct Convert
        {
            template <typename T> static inline
            uint8_t ByteFrom( const T &x ) noexcept { return Gray::UnitToByte(x); }

            template <typename T> static inline
            T ByteTo(const uint8_t u) noexcept { return Color::ByteTo<T>::Unit[u]; }

            template <typename T> static inline
            T RGBATo(const Color::RGBA<uint8_t> &C) noexcept
            {
                return Color::Conv::GrayScale<T>::From(C);
            }

            template <typename T> static inline
            Color::RGBA<uint8_t> ToRGBA(const T &x) noexcept
            {
                const uint8_t u = Gray::UnitToByte(x);
                return Color::RGBA<uint8_t>(u,u,u);
            }

        };
    }

}

#endif // !Y_Color_Conversion_Included

