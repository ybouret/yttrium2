
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

        InputFile:: InputFile(const char * const fileName) :
        File( OpenInputFile(fileName), true)
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

        StdInFile:: StdInFile() :
        File(GetStdIn(),false)
        {

        }

        StdInFile:: ~StdInFile() noexcept
        {
        }
        
    }
}
