
//! \file

#ifndef Y_Color_X11_Included
#define Y_Color_X11_Included

#include "y/color/rgb.hpp"
#include "y/color/x11/defs.hxx"

namespace Yttrium
{
    namespace Color
    {
        //______________________________________________________________________
        //
        //
        //
        //! named X11 color
        //
        //
        //______________________________________________________________________
        struct X11
        {
            const char * name; //!< name
            uint8_t      r;    //!< r
            uint8_t      g;    //!< g
            uint8_t      b;    //!< b

            static const X11    Table[]; //!< database
            static const size_t Count;   //!< num colors
        };
    }
}


#endif // !Y_Color_X11_Included
