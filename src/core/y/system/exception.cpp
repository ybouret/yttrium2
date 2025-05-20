
#if 0
#include "y/system/exception.hpp"
#include "y/core/text.hpp"
#include "y/core/variadic.hpp"
#include <cstring>
#include <cassert>
#include <cstdarg>

namespace Yttrium
{
    namespace Specific
    {
        Exception:: ~Exception() noexcept
        {
            memset(info,0,sizeof(info));
        }

        Exception:: Exception(const char * const title) noexcept :
        Yttrium::Exception(),
        info()
        {
            Core::Text::Copy(info, sizeof(info), title);
        }

        Exception:: Exception(const Exception &other) noexcept :
        Yttrium::Exception(other),
        info()
        {
            memcpy(info, other.info, sizeof(info) );
        }

        const char * Exception:: what() const noexcept
        {
            return info;
        }

        Exception:: Exception(const char * title,
                              const char * formatString,...) noexcept :
        Yttrium::Exception(),
        info()
        {
            assert( 0 != formatString );
            Core::Text::Copy(info, sizeof(info), title);
            va_list ap;
            va_start(ap,formatString);
            (void) Core::Variadic::Format(tell, sizeof(tell), formatString, &ap);
            va_end(ap);
        }
    }

    

}
#endif


