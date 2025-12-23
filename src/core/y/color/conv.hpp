
//! \file

#ifndef Y_Color_Conv_Included
#define Y_Color_Conv_Included

#include "y/color/rgb.hpp"
#include "y/color/rgba.hpp"
#include "y/color/gray.hpp"

namespace Yttrium
{

    namespace Color
    {

        template <typename T>
        RGB<T>:: RGB(const RGBA<T> &c) noexcept :
        r(c.r), g(c.g), b(c.b)
        {

        }

        template <typename T>
        RGB<T> & RGB<T>:: operator=(const RGBA<T> &c) noexcept
        {
            r = c.r;
            g = c.g;
            b = c.b;
            return this;
        }

    }

    namespace Color
    {

        template <typename T>
        RGBA<T>:: RGBA(const RGB<T> &c, const T A ) noexcept :
        r(c.r), g(c.g), b(c.b), a(A)
        {
            
        }

        template <typename T>
        RGBA<T> & RGBA<T>:: operator=(const RGB<T> &c) noexcept
        {
            r = c.r;
            g = c.g;
            b = c.b;
            return this;
        }

    }


    namespace Color
    {
        struct Conv
        {
            //! Gray scale conversion
            template <typename T>
            struct GrayScale
            {
                //! \return float/byte \param r r \param g g \param b b
                static inline
                T From(const uint8_t r, const uint8_t g, const uint8_t b) noexcept
                {
                    return Gray::To<T>::Get(r,g,b);
                }

                //! \return float/byte \param c color with r,g,b
                template <typename COLOR> static inline
                T From(const COLOR &c) noexcept
                {
                    return Gray::To<T>::Get(c.r,c.g,c.b);
                }
            };


        };
    }

}

#endif // !Y_Color_Conv_Included

