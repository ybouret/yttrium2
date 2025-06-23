
//! \file

#ifndef Y_Memory_Static_Output_Stream_Included
#define Y_Memory_Static_Output_Stream_Included 1

#include "y/stream/memory/output.hpp"
#include "y/stream/memory/static.hpp"

namespace Yttrium
{


    template <size_t N>
    class MemoryStaticOutput :
    public MemoryStaticStreamBuffer<N>,
    public MemoryOutput
    {
    public:
        using MemoryStaticStreamBuffer<N>::buff;

        inline explicit MemoryStaticOutput() noexcept :
        MemoryStaticStreamBuffer<N>(),
        MemoryOutput(buff)
        {
        }

        inline virtual ~MemoryStaticOutput() noexcept
        {
        }
        

    private:
        Y_Disable_Copy_And_Assign(MemoryStaticOutput);
    };


}


#endif



