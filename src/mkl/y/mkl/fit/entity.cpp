#include "y/mkl/fit/entity.hpp"

namespace Yttrium
{
    namespace MKL
    {
        namespace Fit
        {
            Entity:: ~Entity() noexcept
            {
            }

            const String & Entity:: key() const noexcept
            {
                return name;
            }
        }
    }

}
