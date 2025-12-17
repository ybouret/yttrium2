
#include "y/concurrent/type/subdivision.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        const char * const Subdivision:: Empty = "|empty|";


#define Y_Subdivision_Ctor() entry(0), bytes(0)

        Subdivision:: Subdivision(const size_t sz, const size_t rk) noexcept :
        Member(sz,rk), Y_Subdivision_Ctor()
        {
        }

        Subdivision:: Subdivision(const Member &m) noexcept :
        Member(m), Y_Subdivision_Ctor()
        {
        }

        Subdivision:: Subdivision(const Subdivision &sub) noexcept :
        Member(sub), Y_Subdivision_Ctor()
        {
        }


        Subdivision:: ~Subdivision() noexcept
        {
        }
        

    }

}

