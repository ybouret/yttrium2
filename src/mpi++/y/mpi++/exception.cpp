#include "y/mpi++/api.hpp"
#include "y/core/variadic.hpp"
#include <cstdarg>
#include <cstring>

namespace Yttrium
{

    MPI:: Exception:: ~Exception() noexcept
    {
        memset(info,0,sizeof(info));
    }

    MPI:: Exception:: Exception(const Exception &excp) noexcept :
    Yttrium::Exception(excp),
    info()
    {
        memcpy(info,excp.info,sizeof(info));
    }

    MPI::Exception:: Exception(const int err, const char * fmt,...) noexcept :
    Yttrium::Exception(),
    info()
    {
        memset(info,0,sizeof(info));
        int resultLen = sizeof(info);
        (void) MPI_Error_string(err,info, &resultLen);
        {
            va_list ap;
            va_start(ap,fmt);
            (void) Core::Variadic::Format(tell, sizeof(tell), fmt, &ap);
            va_end(ap);
        }
    }

    const char * MPI::Exception:: what() const noexcept
    {
        return info;
    }


}

