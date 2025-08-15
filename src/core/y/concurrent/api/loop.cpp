
#include "y/concurrent/api/loop.hpp"
#include "y/system/exception.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        bool Loop::Verbose = false;
        
        Loop:: Loop(const size_t n) :
        size(n)
        {
            if(size<=0) throw Specific::Exception("Concurrent::Loop","null size");
        }

        Loop:: ~Loop() noexcept
        {
        }
        
    }

}
