
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
        

        String Device:: hex() const
        {
            const Parcel<uint8_t> &p = make<uint8_t>();
            if(p.size<=0)
            {
                return '0';
            }
            else
            {
                String          s;
                uint8_t * const b = p.data;
                for(size_t i=p.size;i>0;)
                {
                    s += Hexadecimal::LowerByte[ b[--i] ];
                }
                return s;
            }
        }

    }

}
