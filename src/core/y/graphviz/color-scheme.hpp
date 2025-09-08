
//! \file

#ifndef Y_GraphViz_ColorScheme_Included
#define Y_GraphViz_ColorScheme_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace GraphViz
    {
        //______________________________________________________________________
        //
        //
        //
        //! Built-In ColorScheme
        //
        //
        //______________________________________________________________________
        struct ColorScheme
        {
            const char * name; //!< uuid
            const size_t size; //!< number of sub-colors

            static const ColorScheme Table[]; //!< global table
            static const unsigned    Count;   //!< table size
        };
    }

}


#endif

