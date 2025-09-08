
#include "y/graphviz/color-scheme.hpp"
#include "y/format/decimal.hpp"

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

#define Y_CS39(NAME) \
Y_CS38(NAME), Y_CS(NAME,9)


        const ColorScheme ColorScheme:: Table[] =
        {
            Y_CS38(accent),
            Y_CS39(blues),
            Y_CS39(brbg),
            Y_CS39(bugn),

        };

        const unsigned ColorScheme:: Count = sizeof(Table)/sizeof(Table[0]);


        String  ColorScheme:: operator[](const size_t i) const
        {
            String color = "\"/";
            color += name;
            color += '/';
            { const size_t j = 1 + (i%size); color += Decimal(j).c_str(); }
            color += "\"";
            return color;
        }


    }

}
