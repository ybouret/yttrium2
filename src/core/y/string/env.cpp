#include "y/string/env.hpp"
#include "y/ability/lockable.hpp"
#include "y/string/boolean.hpp"

#include "y/system/platform.hpp"

#if defined(Y_BSD)
#include <cstdlib>
#endif

#if defined(Y_WIN)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "y/exception.hpp"
#include "y/memory/buffer/out-of.hpp"
#include "y/memory/allocator/pooled.hpp"
#endif // defined(Y_WIN)

namespace Yttrium
{
    bool Environment:: Get(String &value, const String &name)
    {
        Y_Giant_Lock();
        value.free();

#if defined(Y_BSD)
        const char * const s = getenv( name.c_str() );
        if(!s) return false;
        value = s;
        return true;
#endif // defined(Y_BSD)

#if defined(Y_WIN)
		DWORD dw = ::GetEnvironmentVariable(name.c_str(), 0, 0);
		if (dw <= 0) return false;
        Memory::BufferOutOf<Memory::Pooled> buff(dw);
        char* const text = (char*)buff.rw();
		const DWORD rd = ::GetEnvironmentVariable(name.c_str(), text, dw);
        if (rd <= 0)
			throw Exception("unexpected vanished '%s'", name.c_str());
        value = String(text); // avoid multiple 0 at end...
        return true;
#endif // defined(Y_WIN)
    }

    bool Environment:: Get(String &value, const char * const name)
    {
        const String _(name);
        return Get(value,_);
    }

    bool Environment:: Flag(const String &name)
    {

        String value;
        if(!Get(value,name)) return false;
        return StringToBoolean:: Get(value, name.c_str() );
    }


    bool Environment::Flag(const char *const name)
    {
        const String _(name); return Flag(_);
    }

}
