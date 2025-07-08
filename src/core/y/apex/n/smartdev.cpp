
#include "y/apex/n/smartdev.hpp"
#include "y/apex/k/device.hpp"

namespace Yttrium
{
    namespace Apex
    {
        SmartDev:: SmartDev(Device * const dev) noexcept :
        device(dev)
        {

        }

        SmartDev:: ~SmartDev() noexcept
        {
            if(device) { delete device; Coerce(device)=0; }
        }
    }

}

