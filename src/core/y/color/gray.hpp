
//! \file

#ifndef Y_Color_Gray_Included
#define Y_Color_Gray_Included

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Color
    {

        struct Gray
        {
            template <typename T>
            struct ByteTo
            {
                static const T Table[256];
            };

        };

    }
}


#endif // !Y_Color_Gray_Included
