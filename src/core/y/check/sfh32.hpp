
//! \file

#ifndef Y_SFH32_Included
#define Y_SFH32_Included 1

#include "y/system/types.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! Super Fast Hash
    //
    //
    //__________________________________________________________________________
    struct SFH32
    {
        //______________________________________________________________________
        //
        //! updated current crc from addr[size]
        //______________________________________________________________________
        static uint32_t Run(uint32_t           hash,
                            const void * const addr,
                            size_t             size) noexcept;

        //______________________________________________________________________
        //
        //! crc of a block
        //______________________________________________________________________
        static uint32_t Of(const void * const addr, size_t size) noexcept;

        

    };

}

#endif
