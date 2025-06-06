
#include "y/type/destroy.hpp"
#include "y/system/wall-time.hpp"
#include "y/object.hpp"
#include "y/system/platform.hpp"
#include "y/type/moniker.hpp"
#include "y/system/exception.hpp"
#include "y/ability/lockable.hpp"

#if defined(Y_Darwin)
#include "wall-time/darwin.hxx"
#endif

#if defined(Y_WIN)
#include "wall-time/win.hxx"
#endif

#if defined(Y_Linux) || defined(Y_FreeBSD) || defined(Y_SunOS) || defined(Y_OpenBSD)
#include "wall-time/clock-gettime.hxx"
#endif

namespace Yttrium
{
    namespace System
    {
        WallTime:: ~WallTime() noexcept
        {
            assert(0!=code);
            Destroy( Coerce(code) );
        }

        WallTime:: WallTime() : code( new Code() )
        {
        }

        long double WallTime:: operator()(const uint64_t ticks) const noexcept
        {
            assert(0!=code);
            return code->convert(ticks);
        }

        long double WallTime:: since(const uint64_t start) const
        {
            assert(0!=code);
            return code->convert( Ticks() - start );
        }

    }

}

