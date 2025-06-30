
//! \file

#ifndef Y_StaticPriorityQueue_Included
#define Y_StaticPriorityQueue_Included 1


#include "y/container/ordered/prio-queue.hpp"
#include "y/memory/buffer/static.hpp"


namespace Yttrium
{
    template <
    typename T,
    const size_t N,
    typename Comparator = Sign::Comparator<T>
    >
    class StaticPriorityQueue :
    protected Memory::StaticBuffer<N*sizeof(T)>,
    public PrioQueue<T>
    {
    public:
        Y_Args_Declare(T,Type);
        typedef Memory::StaticBuffer<N*sizeof(T)> BufferType;
        using BufferType::rw;

        inline explicit StaticPriorityQueue() noexcept :
        BufferType(),
        PrioQueue<T>( static_cast<T *>(rw()),N),
        compare()
        {}

        inline virtual ~StaticPriorityQueue() noexcept {}

        inline void push(ParamType args) {
            this->push(args,compare);
        }

    private:
        Y_Disable_Copy_And_Assign(StaticPriorityQueue);
        mutable Comparator compare;
    };
}

#endif

