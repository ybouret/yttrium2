

//! \file

#ifndef Y_Memory_ReadWriteBuffer_Included
#define Y_Memory_ReadWriteBuffer_Included 1

#include "y/memory/buffer/ro.hpp"

namespace Yttrium
{
    namespace Memory
    {

        class ReadWriteBuffer : public ReadOnlyBuffer
        {
        protected:
            explicit ReadWriteBuffer() noexcept;
        public:
            virtual ~ReadWriteBuffer() noexcept;
            
            void * rw() noexcept;

        private:
            Y_Disable_Copy_And_Assign(ReadWriteBuffer);
        };
    }

}

#endif
