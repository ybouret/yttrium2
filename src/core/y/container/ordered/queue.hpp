//! \file

#ifndef Y_Queue_Included
#define Y_Queue_Included 1


#include "y/core/setup.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! base class for linear queues
    //
    //
    //__________________________________________________________________________
    class Queue
    {
    public:
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup \param numObjects set as capacity
        explicit Queue(const size_t numObjects) noexcept;

        //! cleanup
        virtual ~Queue() noexcept;


        //______________________________________________________________________
        //
        //
        // Members
        //
        //______________________________________________________________________
        const size_t        size;       //!< stored objects
        const size_t        capacity;   //!< maximum stored objects

    private:
        Y_Disable_Copy_And_Assign(Queue); //!< discarding
    };

}

#endif // !Y_Queue_Included
