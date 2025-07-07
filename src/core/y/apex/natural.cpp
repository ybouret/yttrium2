
#include "y/apex/natural.hpp"
#include "y/apex/k/device.hpp"
#include "y/type/destroy.hpp"

namespace Yttrium
{
    namespace Apex
    {

        OpsMode            Natural:: Ops      = Ops32_64;
        PlanType           Natural:: Cmp      = Device::SmallPlan[Ops];
        const char * const Natural:: CallSign = "apn";

        Natural:: Natural() :
        Number(),
        seal(),
        device( new Device(sizeof(uint64_t), Device::SmallPlan[Ops]) )
        {

        }

        Natural:: Natural(const Natural &n) :
        Number(),
        seal(),
        device( new Device( *n.device ) )
        {

        }

        size_t Natural:: serialize(OutputStream &fp) const
        {
            assert(device);
            Y_Lock(seal);
            return device->srz(fp);
        }

        Natural & Natural:: xch( Natural &n ) noexcept
        {
            CoerceSwap(device,n.device);
            return *this;
        }

        size_t Natural:: bits() const noexcept
        {
            assert(device);
            return device->bits;
        }

        Natural & Natural:: operator=( const Natural &n )
        {
            Natural tmp(n);
            return  xch(tmp);
        }


        Natural:: Natural(const natural_t n) :
        Number(),
        device( new Device(CopyOf,n) )
        {
        }

        Natural & Natural:: operator=(const natural_t n)
        {
            device->ld(n);
            return *this;
        }

        Natural:: ~Natural() noexcept
        {
            Destroy(device);
        }

        std::ostream & operator<<(std::ostream &os, const Natural &self)
        {
            Y_Lock(self.seal);
            return os << self.device->hex();
        }

        Natural:: Natural(const TwoToThePowerOf_ &, const size_t n) :
        Number(),
        device(0)
        {
            static const uint8_t bit[8] = { 1,2,4,8,16,32,64,128 };
            const size_t         ibit   = n+1;
            const size_t         size   = Alignment::On<8>::Ceil(ibit)/8;
            Coerce(device) = new Device(size,Plan8);
            if(ibit>0)
            {
                Parcel<uint8_t> &p = device->get<uint8_t>();
                p.data[n>>3] = bit[n&7];
                p.size = size;
                assert(p.sanity());
            }
            Coerce(device->bits) = ibit;
            device->com();
            assert(device->api->bits()==ibit);
        }

    }

}

#include "y/random/bits.hpp"

namespace Yttrium
{
    namespace Apex
    {
        Natural:: Natural(Random::Bits &ran, const size_t numBits) :
        Number(),
        device(0)
        {
            const size_t ceilBits = Alignment::On<8>::Ceil(numBits);
            const size_t numBytes = ceilBits/8;
            Coerce(device)        = new Device(numBytes,Plan8);
            Parcel<uint8_t> & p   = device->get<uint8_t>();
            if(numBytes>0)
            {
                const size_t msi = numBytes - 1;
                for(size_t i=0;i<msi;++i) p.data[i] = ran.to<uint8_t>();
                const size_t rem = numBits - msi * 8;
                if(rem>0) p.data[msi] = ran.to<uint8_t>(rem);
            }
            p.size = numBytes;
            assert( p.sanity() );
            assert( numBits == p.bits() );
            Coerce(device->bits) = numBits;
            device->com();
        }
    }
}
