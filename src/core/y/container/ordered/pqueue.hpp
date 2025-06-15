//! \file

#ifndef Y_PQueue_Included
#define Y_PQueue_Included 1


#include "y/core/setup.hpp"

namespace Yttrium
{

    //! base class for 
    class PQueue
    {
    public:
        explicit PQueue(const size_t numObjects) noexcept;
        virtual ~PQueue() noexcept;

        static inline size_t Parent(size_t pos) noexcept {
            return --pos >> 1;
        }

        const size_t        size;
        const size_t        capacity;

    private:
        Y_Disable_Copy_And_Assign(PQueue);
    };

}

#endif
