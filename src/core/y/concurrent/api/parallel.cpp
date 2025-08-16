
#include "y/concurrent/api/parallel.hpp"
#include "y/system/exception.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        Parallel:: ~Parallel() noexcept
        {
        }


        Parallel:: Parallel(const size_t n, const char * const id) :
        size(n)
        {
            assert(id);
            if(size<=0) throw Specific::Exception(id,"null size");
        }

    }

}
