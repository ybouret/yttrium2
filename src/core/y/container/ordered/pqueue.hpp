//! \file

#ifndef Y_PQueue_Included
#define Y_PQueue_Included 1


#include "y/object.hpp"

namespace Yttrium
{

    class PQueue : public Object
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
