#include "y/core/variadic.hpp"
#include "y/check/usual.hpp"
#include <cstdarg>

namespace Yttrium
{
    namespace Core
    {
        int Variadic:: Format(char * const       outputBuffer,
                              const size_t       outputLength,
                              const char * const formatString,
                              void * const       vaListAddress) noexcept
        {
            assert( Good(outputBuffer,outputLength) || Die("invalid buffer")                      );
            assert( 0!=formatString                 || Die("invalid format string")               );
            assert( 0!=vaListAddress                || Die("ptr must be a valid va_list address") );

            va_list & ap = *static_cast<va_list *>(vaListAddress);
            return vsnprintf(outputBuffer, outputLength, formatString, ap);
        }

        int Variadic:: Sprintf(char * const       outputBuffer,
                               const size_t       outputLength,
                               const char * const formatString,
                               ...) noexcept
        {
            assert( Good(outputBuffer,outputLength) || Die("invalid buffer")                      );
            assert( 0!=formatString                 || Die("invalid format string")               );

            va_list ap;
            va_start(ap,formatString);
            const int res = Format(outputBuffer,outputLength,formatString,&ap);
            va_end(ap);
            return res;
        }


    }
}

