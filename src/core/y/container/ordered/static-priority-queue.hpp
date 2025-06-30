
//! \file

#ifndef Y_StaticPriorityQueue_Included
#define Y_StaticPriorityQueue_Included 1


#include "y/container/ordered/prio-queue.hpp"
#include "y/memory/buffer/static.hpp"


namespace Yttrium
{
    template <typename T, const size_t N>
    class StaticPriorityQueue :
    protected Memory::StaticBuffer<N*sizeof(T)>,
    public PrioQueue<T>
    {
    public:
        typedef Memory::StaticBuffer<N*sizeof(T)> BufferType;
        using BufferType::rw;

        inline explicit StaticPriorityQueue() noexcept :
        BufferType(),
        PrioQueue<T>(rw(),N) {}

        inline virtual ~StaticPriorityQueue() noexcept {}
        
    private:
        Y_Disable_Copy_And_Assign(StaticPriorityQueue);
    };
}

#endif

