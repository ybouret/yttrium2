

#include "y/ink/zero-flux.hpp"

namespace Yttrium
{
    namespace Ink
    {

        ZeroFlux:: ~ZeroFlux() noexcept
        {
        }

        ZeroFlux:: ZeroFlux(const size_t n) noexcept :
        count( (unit_t)n ),
        twice( 2*count-1 )
        {

        }

        ZeroFlux:: ZeroFlux(const ZeroFlux &z) noexcept :
        count( z.count ),
        twice( z.twice )
        {
        }

    }

}

