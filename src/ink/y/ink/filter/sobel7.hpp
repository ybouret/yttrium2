

//! \file

#ifndef Y_Ink_Filter_Sobel7_Included
#define Y_Ink_Filter_Sobel7_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Ink
    {
        //! definition
        struct Sobel7
        {
            static const char * const Label;       //!< label
            static const int16_t      Table[7][7]; //!< table
        };
    }

}

#endif // !Y_Ink_Filter_Sobel7_Included
