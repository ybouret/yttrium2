

#include "y/ink/ops/collect.hpp"

namespace Yttrium
{
    namespace Ink
    {
        Collect:: Collect(const size_t deltaX,
                          const size_t deltaY) noexcept :
        dx( -(unit_t)deltaX ),
        w( 1 + (deltaX<<1)  ),
        dy( -(unit_t)deltaY ),
        h( 1 + (deltaY<<1)  ),
        items( w*h )
        {

        }

        Collect:: ~Collect() noexcept
        {
            
        }
    }

}

