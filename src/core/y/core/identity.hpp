
#ifndef Y_Core_Identity_Included
#define Y_Core_Identity_Included 1

#include "y/system/compiler.hpp"

namespace Yttrium
{

    namespace Core
    {

        template <typename T> inline
        T & Id( T &arg ) noexcept { return arg; }
    }

}

#endif
