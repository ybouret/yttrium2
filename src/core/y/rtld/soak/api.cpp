#include "y/rtld/soak/api.hpp"

#include <cassert>
#include <cstring>

namespace Yttrium
{

    SoakAPI:: SoakAPI() noexcept : Identifiable()
    {
        NoError();
    }

    SoakAPI:: ~SoakAPI() noexcept
    {
    }

    void SoakAPI:: NoError() noexcept
    {
        memset(What,0,sizeof(What));
        memset(When,0,sizeof(When));
    }

    void SoakAPI:: onValid() const noexcept
    {
        NoError();
        strncpy(What, callSign(), sizeof(What)-1);
    }


    char SoakAPI:: What[] = { 0 };
    char SoakAPI:: When[] = { 0 };
    const char * const SoakAPI:: UnhandledException = "unhandled exception";
    
    void SoakAPI:: OnError(const std::exception &excp, const char * const when) noexcept
    {
        assert(0!=when);
        NoError();
        strncpy(What, excp.what(), sizeof(What)-1);
        strncpy(When, when,        sizeof(When)-1);
    }

    void SoakAPI:: OnError(const Exception &excp) noexcept
    {
        NoError();
        strncpy(What, excp.what(), sizeof(What)-1);
        strncpy(When, excp.when(), sizeof(When)-1);
    }

    void SoakAPI:: OnError(const char * const what, const char * const when) noexcept
    {
        assert(0!=what);
        assert(0!=when);
        NoError();
        strncpy(What, what, sizeof(What)-1);
        strncpy(When, when, sizeof(When)-1);
    }

}
