
//! \file

#ifndef Y_GraphViz_ColorScheme_Included
#define Y_GraphViz_ColorScheme_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace GraphViz
    {
        struct ColorScheme
        {
            const char * name;
            const size_t size;

            static const ColorScheme Table[];
            static const unsigned    Count;
        };
    }

}


#endif

