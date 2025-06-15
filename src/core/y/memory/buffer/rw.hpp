

//! \file

#ifndef Y_Memory_ReadWriteBuffer_Included
#define Y_Memory_ReadWriteBuffer_Included 1

#include "y/memory/buffer/ro.hpp"

namespace Yttrium
{
    namespace Memory
    {

        //______________________________________________________________________
        //
        //
        //
        //! Read/Write buffer is a writable ReadOnlyBuffer
        //
        //
        //______________________________________________________________________
        class ReadWriteBuffer : public ReadOnlyBuffer
        {
        protected:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit ReadWriteBuffer() noexcept;
        public:
            virtual ~ReadWriteBuffer() noexcept;

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            void * rw() noexcept; //!< \return writable current address

        private:
            Y_Disable_Copy_And_Assign(ReadWriteBuffer); //!< discarding
        };
    }

}

#endif
