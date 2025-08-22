#include "y/ink/bitrow.hpp"

namespace Yttrium
{
    namespace Ink
    {
        BitRow:: BitRow(void * const    ptr,
                        const size_t    W,
                        const ZeroFlux &Z) noexcept :
        p(ptr),
        w(W),
        z(Z)
        {

        }
    }

}

