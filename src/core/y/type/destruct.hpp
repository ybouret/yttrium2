
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

    //! in-place destruction with case
    /**
     \param addr address of the object to destruct
     */
    template <typename T> inline
    void DestructAs(void * const addr) noexcept
    {
        assert(0!=addr);
        Destruct( static_cast<T *>(addr) );
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
