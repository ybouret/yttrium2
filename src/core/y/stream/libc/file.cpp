#include "y/stream/libc/file.hpp"
#include <cassert>

namespace Yttrium
{
    namespace Libc
    {

        File:: ~File() noexcept
        {
            assert(0!=handle);
            if(mustClose)
            {
                (void) fclose(handle);
            }
            Coerce(handle) = 0;
        }


        File:: File(FILE * const userFile,
                    const bool closeOnQuit) noexcept :
        handle( userFile ),
        mustClose( closeOnQuit )
        {
            
        }


    }
}
