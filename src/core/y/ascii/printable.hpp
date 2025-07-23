//! \file

#ifndef Y_Text_ASCII_Printable_Included
#define Y_Text_ASCII_Printable_Included 1

#include "y/system/compiler.hpp"


namespace Yttrium
{
    namespace ASCII
    {
        //______________________________________________________________________
        //
        //
        //
        //! escaped chars to display output
        //
        //
        //______________________________________________________________________
        struct Printable
        {
            static const char * const Char[256];                 //!< table of substitutions
            static const char *       Text(const char) noexcept; //!< convert char to text
        };

    }
}

#endif

