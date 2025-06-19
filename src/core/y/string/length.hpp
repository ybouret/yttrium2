
//!\ file


#ifndef Y_String_Length_Included
#define Y_String_Length_Included 1

#include "y/system/compiler.hpp"

namespace Yttrium
{


    template <typename T>
    inline size_t StringLength(const T * const s) noexcept
    {
        if(0==s) return 0;
        const T * p = s;
        while( 0 != *p ) ++p;
        return static_cast<size_t>(p-s);
    }


}
#endif
