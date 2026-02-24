
//! \file

#ifndef Y_Ink_Histogram_Otsu_Included
#define Y_Ink_Histogram_Otsu_Included 1

#include "y/ink/histogram.hpp"

namespace Yttrium
{
    namespace Ink
    {

        struct Otsu
        {
            static uint8_t Threshold(const Histogram &) noexcept;
        };

    }

}

#endif // !Y_Ink_Histogram_Otsu_Included

