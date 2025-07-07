
#include "y/apex/k/device.hpp"

namespace Yttrium
{
    namespace Apex
    {

        Device:: ~Device() noexcept
        {
        }

        Device:: Device(const size_t   userBlockSize,
                        const PlanType userBlockPlan) :
        Object(),
        Parcels(userBlockSize,userBlockPlan),
        bits(0),
        bytes( parcel<uint8_t>().size ),
        space( parcel<uint8_t>().maxi )
        {
        }

        Device:: Device(const Device &dev) :
        Object(),
        Parcels(dev),
        bits(dev.bits),
        bytes( parcel<uint8_t>().size ),
        space( parcel<uint8_t>().maxi )
        {
            
        }

    }

}
