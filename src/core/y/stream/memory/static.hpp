
//! \file

#ifndef Y_Memory_Static_Stream_Buffer_Included
#define Y_Memory_Static_Stream_Buffer_Included 1

#include "y/memory/buffer/static.hpp"

namespace Yttrium
{


    template <size_t N>
    class MemoryStaticStreamBuffer
    {
    public:
        inline explicit MemoryStaticStreamBuffer() noexcept : buff() {}
        inline virtual ~MemoryStaticStreamBuffer() noexcept  {}


    protected:
        Memory::StaticBuffer<N> buff;

    private:
        Y_Disable_Copy_And_Assign(MemoryStaticStreamBuffer);
    };


}


#endif



