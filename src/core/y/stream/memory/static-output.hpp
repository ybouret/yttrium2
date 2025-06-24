
//! \file

#ifndef Y_Memory_Static_Output_Stream_Included
#define Y_Memory_Static_Output_Stream_Included 1

#include "y/stream/memory/output.hpp"
#include "y/stream/memory/static.hpp"

namespace Yttrium
{


    //! local memory output stream
    template <size_t N>
    class MemoryStaticOutput :
    public MemoryStaticStreamBuffer<N>,
    public MemoryOutput
    {
    public:
        using MemoryStaticStreamBuffer<N>::buff;

        //! setup
        inline explicit MemoryStaticOutput() noexcept :
        MemoryStaticStreamBuffer<N>(),
        MemoryOutput(buff)
        {
        }

        //! cleanup
        inline virtual ~MemoryStaticOutput() noexcept
        {
        }
        

    private:
        Y_Disable_Copy_And_Assign(MemoryStaticOutput); //!< discarding
    };


}


#endif



