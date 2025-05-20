#include "y/system/error.hpp"
#include "y/core/text.hpp"
#include "y/check/usual.hpp"
#include "y/core/setup.hpp"

#include <cstring>
#if defined(_MSC_VER)
#  pragma warning ( disable : 4996 )
#endif

namespace Yttrium
{
    namespace Libc
    {
        char * Error::Format(char * const errorBuffer,
                             const size_t errorLength,
                             const Type   errorCode) noexcept
        {
            assert(Good(errorBuffer, errorLength));
            return Core::Text::Copy(errorBuffer, errorLength, strerror(errorCode));
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
        char * Error::Format(char * const errorBuffer,
                             const size_t errorLength,
                             const Type   errorCode) noexcept
        {
            assert(Good(errorBuffer, errorLength));
            ::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,
                            0,
                            errorCode,
                            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                            errorBuffer,
                            DWORD(errorLength),
                            0);
            return Core::Text::Trim(errorBuffer);
        }
    }
}
#else
namespace Yttrium
{
    namespace Windows
    {
        char * Error::Format(char * const errorBuffer,
                             const size_t errorLength,
                             const Type ) noexcept
        {
            assert(Good(errorBuffer, errorLength));
            return Core::Text::Copy(errorBuffer, errorLength, Core::Unknown);
        }
    }

}
#endif

#include <iostream>
namespace Yttrium
{
    template <typename ERROR> static inline
    void OnCritical(const typename  ERROR::Type err)
    {
        char buffer[256];
        ERROR::Format(buffer,sizeof(buffer),err);
        std::cerr << "*** Critical Error Detected" << std::endl;
        std::cerr << "*** " << buffer << std::endl;
    }

    namespace Libc
    {
        void Error::Critical(const Type errorCode)
        {
            OnCritical<Error>(errorCode);
        }
    }

    namespace Windows
    {
        void Error::Critical(const Type errorCode)
        {
            OnCritical<Error>(errorCode);
        }
    }

}

