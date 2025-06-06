
//! \file

#ifndef Y_Type_Destroy_Included
#define Y_Type_Destroy_Included 1

#include "y/core/setup.hpp"
#include <cassert>

namespace Yttrium
{
    template <typename T> inline
    void Destroy( T * const & obj ) noexcept
    {
        delete obj;
        Coerce(obj) = 0;
    }
}

#endif
