#include "y/rtld/spyndle/api.hpp"
#include <cstring>
#include <cassert>

namespace Yttrium
{

    char SpyndleAPI:: What[] = { 0 };
    char SpyndleAPI:: When[] = { 0 };

    void SpyndleAPI:: NoMessage() noexcept
    {
        memset(What,0,sizeof(What));
        memset(When,0,sizeof(When));
    }

    void SpyndleAPI:: OnError(const char * const what, const char * const when) noexcept
    {
        assert(what);
        assert(when);
        strncpy(What,what,sizeof(What)-1);
        strncpy(When,when,sizeof(When)-1);
    }

    void SpyndleAPI:: OnError(const std::exception &excp, const char * const when) noexcept
    {
        assert(when);
        assert(excp.what());
        strncpy(What,excp.what(),sizeof(What)-1);
        strncpy(When,when,       sizeof(When)-1);
    }

    void SpyndleAPI:: OnError(const Exception &excp) noexcept
    {
        assert(excp.what());
        assert(excp.when());
        strncpy(What,excp.what(),sizeof(What)-1);
        strncpy(When,excp.when(),sizeof(When)-1);
    }


}

