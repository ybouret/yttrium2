

#include "y/memory/buffer/rw.hpp"

namespace Yttrium
{
    namespace Memory
    {
        ReadWriteBuffer:: ReadWriteBuffer() noexcept : ReadOnlyBuffer()
        {

        }

        ReadWriteBuffer:: ~ReadWriteBuffer() noexcept
        {
        }

        void * ReadWriteBuffer:: rw() noexcept
        {
            return (void*) ro();
        }

    }

}


