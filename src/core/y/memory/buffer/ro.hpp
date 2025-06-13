
//! \file

#ifndef Y_Memory_ReadOnlyBuffer_Included
#define Y_Memory_ReadOnlyBuffer_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Memory
    {

        class ReadOnlyBuffer
        {
        protected:
            explicit ReadOnlyBuffer() noexcept;
        public:
            virtual ~ReadOnlyBuffer() noexcept;

            virtual const void * ro()      const noexcept = 0;
            virtual size_t       length()  const noexcept = 0;
            
        private:
            Y_Disable_Copy_And_Assign(ReadOnlyBuffer);
        };
    }

}

#endif
