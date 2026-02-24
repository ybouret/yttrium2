


//! \file

#ifndef Y_Ink_Filter_Prewitt7_Included
#define Y_Ink_Filter_Prewitt7_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Ink
    {
        struct Prewitt7
        {
            static const char * const Label;
            static const int8_t       Table[7][7];
        };
    }

}

#endif // !Y_Ink_Filter_Prewitt7_Included
