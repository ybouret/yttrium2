
#include "y/graphviz/color-scheme.hpp"
#include "y/format/decimal.hpp"
#include "y/exception.hpp"
#include <cstring>

namespace Yttrium
{
    namespace GraphViz
    {

#define Y_CS(NAME,SIZE) { #NAME #SIZE , SIZE }

#define Y_CS8(NAME) \
Y_CS(NAME,3), \
Y_CS(NAME,4), \
Y_CS(NAME,5), \
Y_CS(NAME,6), \
Y_CS(NAME,7), \
Y_CS(NAME,8)

#define Y_CS9(NAME) \
Y_CS8(NAME), \
Y_CS(NAME,9)

#define Y_CS10(NAME) \
Y_CS9(NAME), \
Y_CS(NAME,10)

#define Y_CS11(NAME) \
Y_CS10(NAME), \
Y_CS(NAME,11)

#define Y_CS12(NAME) \
Y_CS11(NAME), \
Y_CS(NAME,12)

        const ColorScheme ColorScheme:: Table[] =
        {
            Y_CS8(accent),
            Y_CS9(blues),
            Y_CS9(brbg),
            Y_CS9(bugn),
            Y_CS9(bupu),
            Y_CS8(dark2),
            Y_CS9(gnbu),
            Y_CS9(greens),
            Y_CS9(greys),
            Y_CS9(oranges),
            Y_CS9(orrd),
            Y_CS12(paired),
            Y_CS9(pastel1),
            Y_CS8(pastel2),
            Y_CS11(piyg),
            Y_CS11(prgn),
            Y_CS9(pubu),
            Y_CS9(pubugn),
            Y_CS11(puor),
            Y_CS9(purd),
            Y_CS9(purples),
            Y_CS11(rdbu),
            Y_CS11(rdgy),
            Y_CS9(rdpu),
            Y_CS11(rdylbu),
            Y_CS11(rdylgn),
            Y_CS9(reds),
            Y_CS9(set1),
            Y_CS8(set2),
            Y_CS12(set3),
            Y_CS11(spectral),
            Y_CS9(ylgn),
            Y_CS9(ylgnbu),
            Y_CS9(ylorbr),
            Y_CS9(ylorrd)
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

        const ColorScheme & ColorScheme:: Query(const char * const uuid)
        {
            assert(0!=uuid);
            for(unsigned i=0;i<Count;++i)
            {
                const ColorScheme &cs = Table[i];
                if( 0 == strcmp(cs.name,uuid) ) return cs;
            }
            throw Specific::Exception("GraphViz::ColorScheme","no '%s'",uuid);
        }

        const ColorScheme & ColorScheme:: Query(const String &uuid)
        {
            return Query( uuid.c_str() );
        }
    }

}
