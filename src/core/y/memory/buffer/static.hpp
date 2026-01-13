

//! \file

#ifndef Y_Memory_StaticBuffer_Included
#define Y_Memory_StaticBuffer_Included 1

#include "y/memory/buffer/rw.hpp"
#include "y/calculus/alignment.hpp"
#include "y/memory/stealth.hpp"

namespace Yttrium
{
    namespace Memory
    {
        //______________________________________________________________________
        //
        //
        //
        //! Static Buffer is a static Read/Write Buffer
        //
        //
        //______________________________________________________________________
        template <size_t N>
        class StaticBuffer : public ReadWriteBuffer
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setyp
            inline explicit StaticBuffer() noexcept : wksp()
            {
                Y_Memory_BZero(wksp);
            }

            //! cleanup
            inline virtual ~StaticBuffer() noexcept
            {
                Y_Memory_BZero(wksp);
            }

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            inline virtual size_t       length() const noexcept { return N;    }
            inline virtual const void * ro()     const noexcept { return wksp; }

        private:
            Y_Disable_Copy_And_Assign(StaticBuffer);      //!< discarding
            void * wksp[ Alignment::WordsGEQ<N>::Count ]; //!< local memory
        };
    }

}

#endif // !Y_Memory_StaticBuffer_Included
