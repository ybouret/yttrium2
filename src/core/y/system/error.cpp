#include "y/system/error.hpp"
#include "y/core/text.hpp"
#include "y/check/usual.hpp"

#include <cstring>

namespace Yttrium
{
    namespace Libc
    {
        void Error:: Format(char * const errorBuffer,
                            const size_t errorLength,
                            const Type   errorCode) noexcept
        {
            assert( Good(errorBuffer,errorLength) );
            memset(errorBuffer,0,errorLength);
            strncpy(errorBuffer,strerror(errorCode),errorLength);
        }
    }
}

#if defined(Y_WIN)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
namespace Yttrium
{
    namespace Windows
    {
        
    }
}
#endif
