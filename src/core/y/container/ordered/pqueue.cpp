
#include "y/container/ordered/pqueue.hpp"
#include <cassert>

namespace Yttrium
{

    PQueue:: PQueue(const size_t numObjects) noexcept :
    Object(),
    size(0),
    capacity(numObjects)
    {
    }

    PQueue:: ~PQueue() noexcept
    {
        assert(0==size);
        Coerce(capacity) = 0;
    }


}

