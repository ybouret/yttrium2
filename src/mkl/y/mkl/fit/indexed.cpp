
#include "y/mkl/fit/indexed.hpp"
#include <cstring>

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {
            Indexed:: ~Indexed() noexcept
            {
            }

            void Indexed:: setup(const size_t primaryIndex) noexcept
            {
                memset( &Coerce(indx[0]), 0, sizeof(indx) );
                Coerce(indx[PrimaryLevel]) = primaryIndex;
            }

        }
    }

}
