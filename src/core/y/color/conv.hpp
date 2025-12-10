
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
        RGBA<T>:: RGBA(const RGB<T> &c, const T A ) noexcept :
        r(c.r), g(c.g), b(c.b), a(A)
        {
            
        }

    }

}

#endif // !Y_Color_Conv_Included

