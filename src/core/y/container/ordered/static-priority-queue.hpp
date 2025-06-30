
//! \file

#ifndef Y_StaticPriorityQueue_Included
#define Y_StaticPriorityQueue_Included 1


#include "y/container/ordered/prio-queue.hpp"
#include "y/memory/buffer/static.hpp"
#include "y/type/ingress.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! fast inline static priority queue
    //
    //
    //__________________________________________________________________________
    template <
    typename T,
    const size_t N,
    typename Comparator = Sign::Comparator<T>
    >
    class StaticPriorityQueue : public Ingress< const PrioQueue<T> >
    {
    public:
        //______________________________________________________________________
        //
        //
        // Definitions
        //
        //______________________________________________________________________
        Y_Args_Declare(T,Type);                               //!< aliases
        typedef Memory::StaticBuffer<N*sizeof(T)> BufferType; //!< alias
        typedef PrioQueue<T>                      QueueType;  //!< alias

        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup
        inline explicit StaticPriorityQueue() noexcept :
        __(),
        pq( static_cast<MutableType *>(__.rw()),N),
        compare()
        {}

        //! cleanup
        inline virtual ~StaticPriorityQueue() noexcept {}

        //! insert \param args data \return *this
        inline StaticPriorityQueue & operator <<(ParamType args)
        {
            pq.push(args,compare);
            return *this;
        }

        //! extract \return top element
        inline ConstType pop() noexcept
        {
            return pq.pop(compare);
        }



    private:
        Y_Disable_Copy_And_Assign(StaticPriorityQueue); //!< discaring
        BufferType         __;      //!< internal memory
        QueueType          pq;      //!< internal queue
        mutable Comparator compare; //!< comparator

        virtual const QueueType & locus() const noexcept { return pq; }
    };
}

#endif

