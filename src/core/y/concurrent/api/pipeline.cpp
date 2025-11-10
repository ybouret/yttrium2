
#include "y/concurrent/api/pipeline.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        
        Pipeline:: Pipeline(const size_t n, const char * const id) :
        Parallel(n,id),
        counter(0)
        {
        }

        Pipeline:: ~Pipeline() noexcept
        {
        }


        


    }

}
