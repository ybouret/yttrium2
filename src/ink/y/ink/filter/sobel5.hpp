
//! \file

#ifndef Y_Ink_Filter_Sobel5_Included
#define Y_Ink_Filter_Sobel5_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Ink
    {
        //! definition
        struct Sobel5
        {
            static const char * const Label;       //!< label
            static const int8_t       Table[5][5]; //!< table
        };
    }

}

#endif // !Y_Ink_Filter_Sobel5_Included
