
//! \file

#ifndef Y_Libc_File_Buffer_Included
#define Y_Libc_File_Buffer_Included 1

#include "y/stream/libc/file.hpp"
#include "y/memory/buffer/out-of.hpp"
#include "y/memory/allocator/quanta.hpp"

namespace Yttrium
{
    namespace Libc
    {
        typedef Memory::BufferOutOf<Memory::Quanta> FileBufferType;

        class FileBuffer : public FileBufferType
        {
        public:
            explicit FileBuffer();
            virtual ~FileBuffer() noexcept;

            void operator()(File &) noexcept;

        private:
            Y_Disable_Copy_And_Assign(FileBuffer);
        };
    }

}


#endif
