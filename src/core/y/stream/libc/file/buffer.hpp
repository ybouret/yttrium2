
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
        //______________________________________________________________________
        //
        //! base class for file buffer
        //______________________________________________________________________
        typedef Memory::BufferOutOf<Memory::Quanta> FileBufferType;

        //______________________________________________________________________
        //
        //
        //
        //! Memory to bufferize FILE
        //
        //
        //______________________________________________________________________
        class FileBuffer : public FileBufferType
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit FileBuffer();          //!< setup
            virtual ~FileBuffer() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! use memory to setvbuf
            void bufferize(File &) noexcept;

        private:
            Y_Disable_Copy_And_Assign(FileBuffer); //!< discarding
        };
    }

}


#endif
