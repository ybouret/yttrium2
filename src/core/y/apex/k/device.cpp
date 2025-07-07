
#include "y/apex/k/device.hpp"

namespace Yttrium
{
    namespace Apex
    {

        const PlanType Device:: SmallPlan[NumOps] =
        {
            Plan8,
            Plan8,
            Plan8,

            Plan16,
            Plan16,

            Plan32
        };




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

        void Device:: com()  noexcept
        {
            assert(api->sanity());
            ParcelAPI:: Propagate(sync[plan],bits);
        }

        Device:: Device(const CopyOf_ &, const uint64_t n) :
        Object(),
        Parcels(sizeof(n),Plan64),
        Y_Apex_Device( Calculus::BitsFor::Count(n) )
        {
            if(bits>0)
            {
                Parcel<uint64_t> &p = get<uint64_t>();
                p.data[0] = n;
                p.size    = 1;
                assert(p.sanity());
                com();
            }
        }


        void Device:: ld(const uint64_t n) noexcept
        {
            Parcel<uint64_t> &p = make<uint64_t>();
            p.naught(sync[Plan64]);
            if(n>0)
            {
                p.data[0] = n;
                p.size    = 1;
                assert(p.sanity());
                Coerce(bits) = Calculus::BitsFor::Count(n);
                com();
            }
            else
            {
                Coerce(bits) = 0;
            }
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
