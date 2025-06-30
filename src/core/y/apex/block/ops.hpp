
//! \file

#ifndef Y_Apex_Block_Ops_Included
#define Y_Apex_Block_Ops_Included 1

#include "y/system/compiler.hpp"

namespace Yttrium
{
    namespace Apex
    {
        //______________________________________________________________________
        //
        //
        //! internal operations mode
        //
        //______________________________________________________________________
        enum OpsMode
        {
            Ops8_16,  //!< inner:  8-bits outer: 16-bits
            Ops8_32,  //!< inner:  8-bits outer: 32-bits
            Ops8_64,  //!< inner:  8-bits outer: 64-bits

            Ops16_32, //!< inner: 16-bits outer: 32-bits
            Ops16_64, //!< inner: 16-bits outer: 64-bits

            Ops32_64  //!< inner: 32-bits outer: 64-bits
        };
    }

}

#endif
