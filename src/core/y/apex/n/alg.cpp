#include "y/apex/natural.hpp"
#include "y/apex/k/device.hpp"

namespace Yttrium
{
    namespace Apex
    {
        Natural Natural:: abs() const
        {
            return *this;
        }

        void Natural:: shr() noexcept
        {
            device->shr();
        }
    }

}

