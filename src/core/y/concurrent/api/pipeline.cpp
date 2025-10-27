
#include "y/concurrent/api/pipeline.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        //bool SIMD::Verbose = false;

        Pipeline:: Pipeline(const size_t n, const char * const id) :
        Parallel(n,id)
        {
        }

        Pipeline:: ~Pipeline() noexcept
        {
        }

    }

}
