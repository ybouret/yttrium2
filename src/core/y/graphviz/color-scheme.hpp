
//! \file

#ifndef Y_GraphViz_ColorScheme_Included
#define Y_GraphViz_ColorScheme_Included 1

#include "y/string.hpp"

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

            String  operator[](const size_t) const; //!< return formatted color

            static const ColorScheme   Table[]; //!< global table
            static const unsigned      Count;   //!< table size
            static const ColorScheme & Query(const char * const);
            static const ColorScheme & Query(const String &);

        };
    }

}


#endif

