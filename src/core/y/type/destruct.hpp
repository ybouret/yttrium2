
//! \file

#ifndef Y_Type_Destruct_Included
#define Y_Type_Destruct_Included 1

#include "y/system/compiler.hpp"
#include <cassert>

namespace Yttrium
{
    template <typename T> inline
    void Destruct(T * const obj) noexcept
    {
        assert(0!=obj);
        obj->~T();
    }

    template <typename T> inline
    T * Destructed(T * const obj) noexcept
    {
        assert(0!=obj);
        Destruct(obj);
        return obj;
    }

    template <typename T> inline
    void Nullify(T * & obj) noexcept
    {
        assert(0!=obj);
        Destruct(obj);
        obj = 0;
    }

}

#endif
