
#include "y/apex/k/device.hpp"

namespace Yttrium
{
    namespace Apex
    {

        Device:: ~Device() noexcept
        {
        }


#define Y_Apex_Device(BITS) \
bits(BITS),\
bytes( parcel<uint8_t>().size ),\
space( parcel<uint8_t>().maxi )

        Device:: Device(const size_t   userBlockSize,
                        const PlanType userBlockPlan) :
        Object(),
        Parcels(userBlockSize,userBlockPlan),
        Y_Apex_Device(0)
        {
        }

        Device:: Device(const Device &dev) :
        Object(),
        Parcels(dev),
        Y_Apex_Device(dev.bits)
        {
            
        }

        Device:: Device(const uint64_t n) :
        Object(),
        Parcels(sizeof(n),Plan64),
        Y_Apex_Device( Calculus::BitsFor::Count(n) )
        {
        }
        


        
    }

}
