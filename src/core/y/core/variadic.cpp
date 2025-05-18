#include "y/core/variadic.hpp"
#include "y/check/usual.hpp"
#include <cstdarg>

namespace Yttrium
{
    namespace Core
    {
        int Variadic:: Format(char * const       buf,
                              const size_t       len,
                              const char * const fmt,
                              void * const       ptr) noexcept
        {
            assert( Good(buf,len) || Die("invalid buffer")                      );
            assert( 0!=fmt        || Die("invalid format string")               );
            assert( 0!=ptr        || Die("ptr must be a valid va_list address") );

            va_list & ap = *static_cast<va_list *>(ptr);
            return vsnprintf(buf, len, fmt, ap);
        }

        int Variadic:: Sprintf(char *const buf, const size_t len, const char *const fmt, ...) noexcept
        {
            assert( Good(buf,len) || Die("invalid buffer")        );
            assert( 0!=fmt        || Die("invalid format string") );

            va_list ap;
            va_start(ap,fmt);
            const int res = vsnprintf(buf, len, fmt, ap);
            va_end(ap);
            return res;
        }


    }
}

