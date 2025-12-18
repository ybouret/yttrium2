
#include "y/color/x11.hpp"

namespace Yttrium
{
    namespace Color
    {
        const X11  X11::Table[] =
        {
#include "x11/incl.hxx"
        };

        const size_t X11 :: Count = sizeof(Table)/sizeof(Table[0]);
    }
}

