
#include "y/concurrent/api/simd/sole.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        const char * const Sole::CallSign = "Sole";

        Sole:: ~Sole() noexcept
        {
        }

        Sole:: Sole() noexcept :
        SIMD(),
        mutex(),
        context(mutex,1,0)
        {
        }


        const char * Sole:: callSign() const noexcept { return CallSign; }


        void Sole:: operator()( Kernel &k ) noexcept
        {
            k(context);
        }

        size_t Sole:: size() const noexcept
        {
            return 1;
        }

        
    }

}

