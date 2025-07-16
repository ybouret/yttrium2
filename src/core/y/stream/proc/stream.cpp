#include "y/stream/proc/stream.hpp"
#include "y/ability/lockable.hpp"
#include "y/system/exception.hpp"

#include <cstdio>

#if defined(Y_WIN)
#if   defined(_MSC_VER)
#       define WIN32_LEAN_AND_MEAN
#       include <windows.h>
#       define popen  _popen
#       define pclose _pclose
#else // Y_WIN
      // assuming gcc
extern "C" FILE * popen(const char *, const char *);
extern "C" int    pclose(FILE *);
#endif // Y_WIN
#endif

namespace Yttrium
{

    ProcessStream:: ~ProcessStream() noexcept
    {
        assert(0!=handle);
        pclose( (FILE*)handle );
        Coerce(handle) = 0;
    }

    void * call_popen(const char * const cmd,
                      const char * const how)
    {
        assert(0!=cmd);
        assert(0!=how);
        Y_Giant_Lock();
        FILE *fp = popen(cmd,how);
        if(0==fp) throw Specific::Exception("ProcStream", "can't popen('%s','%s'", cmd, how);
        return fp;
    }

    ProcessStream:: ProcessStream(const char * const cmd,
                                  const char * const how) :
    handle( call_popen(cmd,how) )
    {

    }
    


}

