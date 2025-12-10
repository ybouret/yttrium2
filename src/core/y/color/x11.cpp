
#include "y/color/x11.hpp"

namespace Yttrium
{
    namespace Color
    {
        const X11Color X11Color::Table[] =
        {
#include "x11/incl.hxx"
        };

        const size_t X11Color:: Count = sizeof(X11Color::Table)/sizeof(X11Color::Table[0]);
    }
}

