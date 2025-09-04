
#include "y/string/format.hpp"
#include "y/core/variadic.hpp"
#include "y/system/exception.hpp"
#include <cstdarg>

namespace Yttrium
{
    

    String Formatted::Get(const char * const fmt,...)
    {
        static const char fn[] = "StringFormat";
        assert(fmt!=0);

        size_t length = 0;
        int    result = 0;
        {
            va_list ap;
            va_start(ap,fmt);
            result = Core::Variadic::Format(0,0,fmt, &ap);
            va_end(ap);
            if(result<0)
                throw Specific::Exception(fn,"invalid format string");
            length = size_t( result );
        }

        String str(WithAtLeast,length,true); assert(str.size()==length);

        {
            va_list ap;
            va_start(ap,fmt);
            const int result2 = Core::Variadic::Format( str(),length+1,fmt, &ap);
            if(result2!=result)
                throw Specific::Exception(fn,"corrupted variadic call");
            va_end(ap);
        }
        
        return str;
    }

}
