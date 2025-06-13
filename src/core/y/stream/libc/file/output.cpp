

#include "y/stream/libc/file/output.hpp"
#include "y/ability/lockable.hpp"
#include "y/system/exception.hpp"
#include <cerrno>

namespace Yttrium
{
    namespace Libc
    {
        OutputFile:: ~OutputFile() noexcept
        {
        }

        namespace
        {
            static inline
            FILE * OpenOutputFile(const char * const fileName)
            {
                assert(0!=fileName);
                Y_Giant_Lock();
                FILE * const fp = fopen(fileName, "wb");
                if(!fp)
                    throw Libc::Exception(errno,"fopen(%s)", fileName);
                return fp;
            }
        }

        OutputFile:: OutputFile(const char * const fileName) :
        File( OpenOutputFile(fileName), true)
        {
        }



    }

}


namespace Yttrium
{
    namespace Libc
    {
        static FILE * GetStdErr()
        {
            if(!stderr) throw Specific::Exception("Libc::StdErr","stderr was closed");
            return stderr;
        }

        StdErrFile:: StdErrFile() :
        File(GetStdErr(),false)
        {

        }

        StdErrFile:: ~StdErrFile() noexcept
        {
        }

    }
}


namespace Yttrium
{
    namespace Libc
    {
        static FILE * GetStdOut()
        {
            if(!stdout) throw Specific::Exception("Libc::StdOut","stdout was closed");
            return stdout;
        }

        StdOutFile:: StdOutFile() :
        File(GetStdOut(),false)
        {

        }

        StdOutFile:: ~StdOutFile() noexcept
        {
        }

    }
}
