
//! \file

#ifndef Y_Hardware_Included
#define Y_Hardware_Included 1

#include "y/system/compiler.hpp"

namespace Yttrium
{

    //! Hardware information
    struct Hardware
    {
        static size_t NumProcs(); //!< \return number of logical processors
    };

}

#endif // !Y_Hardware_Included

