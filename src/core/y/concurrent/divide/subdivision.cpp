
#include "y/concurrent/divide/subdivision.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        const char * const Subdivision:: Empty = "|empty|";


        Subdivision:: Subdivision(const size_t sz, const size_t rk) noexcept :
        Member(sz,rk)
        {
        }

        Subdivision:: Subdivision(const Member &m) noexcept :
        Member(m)
        {
        }

        Subdivision:: Subdivision(const Subdivision &sub) noexcept :
        Member(sub)
        {
        }


        Subdivision:: ~Subdivision() noexcept
        {
        }
        

    }

}

