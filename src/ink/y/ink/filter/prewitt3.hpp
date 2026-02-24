
//! \file

#ifndef Y_Ink_Filter_Prewitt3_Included
#define Y_Ink_Filter_Prewitt3_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Ink
    {
        //! definition
        struct Prewitt3
        {
            static const char * const Label;       //!< label
            static const int8_t       Table[3][3]; //!< table
        };
    }

}

#endif // !Y_Ink_Filter_Prewitt3_Included
