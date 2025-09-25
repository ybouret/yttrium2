
//! \file

#ifndef Y_Type_Destroy_Included
#define Y_Type_Destroy_Included 1

#include "y/core/setup.hpp"
#include <cassert>

namespace Yttrium
{

    //! delete and set pointer to NULL
    /**
     \param obj an object created by 'new T(...)'
     */
    template <typename T> inline
    void Destroy( T * const & obj ) noexcept
    {
        delete obj;
        Coerce(obj) = 0;
    }
}

#endif // !Y_Type_Destroy_Included
