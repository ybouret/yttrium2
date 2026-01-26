

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
        items( w*h ),
        ihalf( (items-1) >> 1 )
        {
            assert( 0 != (w&1) );
            assert( 0 != (h&1) );
            assert( 0 != (items&1) );

        }

        Collect:: ~Collect() noexcept
        {
            
        }
    }

}

