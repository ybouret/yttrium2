
#include "y/concurrent/api/simd.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        bool SIMD::Verbose = false;

        SIMD:: SIMD(const size_t n, const char * const id) :
        Parallel(n,id)
        {
        }

        SIMD:: ~SIMD() noexcept
        {
        }
        
    }

}
