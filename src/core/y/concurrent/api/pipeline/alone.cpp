

#include "y/concurrent/api/pipeline/alone.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        const char * const Alone:: CallSign = "Concurrent::Alone";

        Alone:: Alone() :
        Pipeline(1,CallSign)
        {
        }

        Pipeline:: ~Pipeline() noexcept
        {
        }

    }

}
