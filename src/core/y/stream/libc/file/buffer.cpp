
#include "y/stream/libc/file/buffer.hpp"

namespace Yttrium
{
    namespace Libc
    {
        FileBuffer:: ~FileBuffer() noexcept
        {
        }

        FileBuffer:: FileBuffer() : FileBufferType(BUFSIZ)
        {
        }

        void FileBuffer:: operator()(File &f) noexcept
        {
            (void) setvbuf(f.handle, (char *)rw(), _IOFBF, BUFSIZ);
        }


    }
}

