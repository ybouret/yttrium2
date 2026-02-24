


//! \file

#ifndef Y_Ink_Filter_Prewitt7_Included
#define Y_Ink_Filter_Prewitt7_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Ink
    {
        //! definition
        struct Prewitt7
        {
            static const char * const Label;       //!< label
            static const int8_t       Table[7][7]; //!< data
        };
    }

}

#endif // !Y_Ink_Filter_Prewitt7_Included
