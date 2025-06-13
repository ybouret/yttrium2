
#include "y/stream/libc/file/input.hpp"
#include "y/ability/lockable.hpp"
#include "y/system/exception.hpp"
#include <cerrno>

namespace Yttrium
{
    namespace Libc
    {
        InputFile:: ~InputFile() noexcept
        {
        }

#if 0
        namespace
        {
            static inline
            FILE * OpenInputFile(const char * const fileName)
            {
                assert(0!=fileName);
                Y_Giant_Lock();
                FILE * const fp = fopen(fileName, "rb");
                if(!fp)
                    throw Libc::Exception(errno,"fopen(%s)", fileName);
                return fp;
            }
        }
#endif

        InputFile:: InputFile(FILE * const userHandle, const bool closeOnQuit) :
        File(userHandle,closeOnQuit),
        Q()
        {
        }

    }

}

namespace Yttrium
{
    namespace Libc
    {
        RegularInputFile:: ~RegularInputFile() noexcept
        {
        }

        RegularInputFile:: RegularInputFile(FILE * const fp) :
        InputFile(fp,true)
        {
        }
    }

}


namespace Yttrium
{
    namespace Libc
    {
        static FILE * GetStdIn()
        {
            if(!stdin) throw Specific::Exception("Libc::StdIn","stdin was closed");
            return stdin;
        }

        StandarInputFile:: StandarInputFile() :
        InputFile(GetStdIn(),false)
        {

        }

        StandarInputFile:: ~StandarInputFile() noexcept
        {
        }
        
    }
}

