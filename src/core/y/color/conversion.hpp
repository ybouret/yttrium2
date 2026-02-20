
//! \file

#ifndef Y_Color_Conversion_Included
#define Y_Color_Conversion_Included

#include "y/color/conv.hpp"
#include "y/color/rgba.hpp"

namespace Yttrium
{

    namespace Color
    {

        //______________________________________________________________________
        //
        //
        //
        //! default color conversion
        //
        //
        //______________________________________________________________________
        struct Convert
        {
            //! \param x unit floating point \return closest byte
            template <typename T> static inline
            uint8_t ByteFrom( const T &x ) noexcept { return Gray::UnitToByte(x); }

            //! \param u byte \return unit floating point
            template <typename T> static inline
            T ByteTo(const uint8_t u) noexcept { return Color::ByteTo<T>::Unit[u]; }

            //! \param C color \return gray scale as unit floating point/byte
            template <typename T> static inline
            T RGBATo(const Color::RGBA<uint8_t> &C) noexcept
            {
                return Color::Conv::GrayScale<T>::From(C);
            }

            //!  \param x unit floating point/byte \return gray color
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

