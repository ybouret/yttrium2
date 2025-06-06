
//! \file

#ifndef Y_Type_Destruct_Included
#define Y_Type_Destruct_Included 1

#include "y/system/compiler.hpp"
#include <cassert>

namespace Yttrium
{
    //! in-place object destruction
    /**
     \param obj a valid object, destructed upon return
     */
    template <typename T> inline
    void Destruct(T * const obj) noexcept
    {
        assert(0!=obj);
        obj->~T();
    }

    //! in place object destruction
    /**
     \param obj a valid object
     \return address of destructed object
     */
    template <typename T> inline
    T * Destructed(T * const obj) noexcept
    {
        assert(0!=obj);
        Destruct(obj);
        return obj;
    }
    

}

#endif
