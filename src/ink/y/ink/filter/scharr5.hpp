

//! \file

#ifndef Y_Ink_Filter_Scharr5_Included
#define Y_Ink_Filter_Scharr5_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Ink
    {
        struct Scharr5
        {
            static const char * const Label;
            static const int8_t       Table[5][5];
        };
    }

}

#endif // !Y_Ink_Filter_Scharr5_Included
