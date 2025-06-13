

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
        template <size_t N>
        class StaticBuffer : public ReadWriteBuffer
        {
        public:
            inline explicit StaticBuffer() noexcept : wksp()
            {
                Y_Memory_BZero(wksp);
            }

            inline virtual ~StaticBuffer() noexcept
            {
                Y_Memory_BZero(wksp);
            }

            inline virtual size_t       length() const noexcept { return N;    }
            inline virtual const void * ro()     const noexcept { return wksp; }

        private:
            Y_Disable_Copy_And_Assign(StaticBuffer);
            void * wksp[ Alignment::WordsGEQ<N>::Count ];
        };
    }

}

#endif
