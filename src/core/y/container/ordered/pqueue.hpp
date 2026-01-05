//! \file

#ifndef Y_PQueue_Included
#define Y_PQueue_Included 1


#include "y/core/setup.hpp"

namespace Yttrium
{

    //__________________________________________________________________________
    //
    //
    //
    //! base class for priority queues
    //
    //
    //__________________________________________________________________________
    class PQueue
    {
    public:
        //______________________________________________________________________
        //
        //
        // C++
        //
        //______________________________________________________________________

        //! setup \param numObjects set as capacity
        explicit PQueue(const size_t numObjects) noexcept;

        //! cleanup
        virtual ~PQueue() noexcept;

        //______________________________________________________________________
        //
        //
        // Methods
        //
        //______________________________________________________________________

        //! helper \param pos current index \return parent index
        static inline size_t Parent(size_t pos) noexcept {
            return (--pos) >> 1;
        }

        //______________________________________________________________________
        //
        //
        // Members
        //
        //______________________________________________________________________
        const size_t        size;       //!< stored objects
        const size_t        capacity;   //!< maximum stored objects

    private:
        Y_Disable_Copy_And_Assign(PQueue); //!< discarding
    };

}

#endif // !Y_PQueue_Included
