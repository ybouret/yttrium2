//! \file

#ifndef Y_Ink_Filter_Sobel3_Included
#define Y_Ink_Filter_Sobel3_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Ink
    {
        //! definition
        struct Sobel3
        {
            static const char * const Label;       //!< label
            static const int8_t       Table[3][3]; //!< data
        };
    }

}

#endif // !Y_Ink_Filter_Sobel3_Included
