
//! \file

#ifndef Y_Color_X11_Included
#define Y_Color_X11_Included

#include "y/color/rgb.hpp"
#include "y/color/x11/defs.hxx"

namespace Yttrium
{
    namespace Color
    {
        struct X11Color
        {
            const char * name;
            uint8_t      r;
            uint8_t      g;
            uint8_t      b;

            static const X11Color Table[];
            static const size_t   Count;
        };
    }
}


#endif // !Y_Color_X11_Included
