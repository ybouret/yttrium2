

#include "y/container/ordered/queue.hpp"
#include <cassert>

namespace Yttrium
{

    Queue:: Queue(const size_t numObjects) noexcept :
    size(0),
    capacity(numObjects)
    {
    }

    Queue:: ~Queue() noexcept
    {
        assert(0==size);
        Coerce(capacity) = 0;
    }


}

