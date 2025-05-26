
//! \file

#ifndef Y_Memory_Limits_Included
#define Y_Memory_Limits_Included 1

#include "y/system/compiler.hpp"

namespace Yttrium
{
    namespace Memory
    {
        //! Common static limits
        struct Limits
        {
            static const size_t MinBlockBytes = 128; //!< for Object::Chunk and Pages
        };
    }

}

#endif

