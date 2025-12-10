
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
            struct ByteTo {
                static const T Table[256];
            };

            static const size_t  Count = 1 + 3*255;
            static const uint8_t Table[Count];

            static uint8_t Get(const uint8_t r, const uint8_t g, const uint8_t b);
            
        };

    }
}


#endif // !Y_Color_Gray_Included
