
//! \file

#ifndef Y_Apex_Block_View_Included
#define Y_Apex_Block_View_Included 1

#include "y/apex/metrics.hpp"

namespace Yttrium
{
    namespace Apex
    {
        //______________________________________________________________________
        //
        //
        //! internal big-endian representation
        //
        //______________________________________________________________________
        enum ViewType
        {
            View8,  //!< as uint8_t
            View16, //!< as uint16_t
            View32, //!< as uint32_t
            View64  //!< as uint64_t
        };

    }

}

#endif

