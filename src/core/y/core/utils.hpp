
//! \file

#ifndef Y_Core_Utils_Included
#define Y_Core_Utils_Included 1

//#include "y/system/types.hpp"


namespace Yttrium
{

    template <typename T> inline
    T MaxOf(const T a, const T b)
    {
        return a < b ? b : a;
    }

    template <typename T> inline
    T MinOf(const T a, const T b)
    {
        return a < b ? a : b;
    }

}

#endif

