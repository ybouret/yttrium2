
#include "y/graphviz/color-scheme.hpp"

namespace Yttrium
{
    namespace GraphViz
    {

#define Y_CS(NAME,SIZE) { #NAME #SIZE , SIZE }

#define Y_CS38(NAME) \
Y_CS(NAME,3), \
Y_CS(NAME,4), \
Y_CS(NAME,5), \
Y_CS(NAME,6), \
Y_CS(NAME,7), \
Y_CS(NAME,8)


        const ColorScheme ColorScheme:: Table[] =
        {
            Y_CS38(accent)
        };

        const unsigned ColorScheme:: Count = sizeof(Table)/sizeof(Table[0]);
    }

}
