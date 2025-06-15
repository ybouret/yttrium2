
//! \file

#ifndef Y_Memory_ReadOnlyBuffer_Included
#define Y_Memory_ReadOnlyBuffer_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Memory
    {

        //______________________________________________________________________
        //
        //
        //
        //! Read-Only buffer
        //
        //
        //______________________________________________________________________
        class ReadOnlyBuffer
        {
        protected:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit ReadOnlyBuffer() noexcept; //!< setup
        public:
            virtual ~ReadOnlyBuffer() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual const void * ro()      const noexcept = 0; //!< \return current address
            virtual size_t       length()  const noexcept = 0; //!< \return current length

        private:
            Y_Disable_Copy_And_Assign(ReadOnlyBuffer); //!< discarding
        };
    }

}

#endif
