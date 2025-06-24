
//! \file

#ifndef Y_Memory_Static_Stream_Buffer_Included
#define Y_Memory_Static_Stream_Buffer_Included 1

#include "y/memory/buffer/static.hpp"

namespace Yttrium
{

    //! local buffer for local Memory[Input|Output]
    template <size_t N>
    class MemoryStaticStreamBuffer
    {
    public:
        inline explicit MemoryStaticStreamBuffer() noexcept : buff() {} //!< setup
        inline virtual ~MemoryStaticStreamBuffer() noexcept  {}         //!< cleanup


    protected:
        Memory::StaticBuffer<N> buff; //!< local memory

    private:
        Y_Disable_Copy_And_Assign(MemoryStaticStreamBuffer); //!< discarding
    };


}


#endif



