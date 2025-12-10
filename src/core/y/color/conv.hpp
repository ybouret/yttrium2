
//! \file

#ifndef Y_Color_Conv_Included
#define Y_Color_Conv_Included

#include "y/color/rgb.hpp"
#include "y/color/rgba.hpp"

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

}

#endif // !Y_Color_Conv_Included

