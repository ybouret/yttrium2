//! \file

#ifndef Y_Memory_Ownership_Included
#define Y_Memory_Ownership_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Memory
    {

        //! named ownership for addresses
        enum Ownership
        {
            OwnedByPrev, //!< owned by previous object
            OwnedByCurr, //!< owned by this object
            OwnedByNext  //!< owned by newxt object
        };
    }

}

#endif

