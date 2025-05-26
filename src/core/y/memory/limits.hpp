
//! \file

#ifndef Y_Memory_Limits_Included
#define Y_Memory_Limits_Included 1

#include "y/system/compiler.hpp"

namespace Yttrium
{
    namespace Memory
    {

        struct Limits
        {
            static const size_t MinBlockBytes = 128;
        };
    }

}

#endif

