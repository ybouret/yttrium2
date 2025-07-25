
#include "y/apex/natural.hpp"
#include "y/apex/k/device.hpp"
#include "y/type/destroy.hpp"

namespace Yttrium
{
    namespace Apex
    {

        OpsMode            Natural:: Ops      = Ops32_64;
        PlanType           Natural:: Cmp      = Device::SmallPlan[Ops];
        PlanType           Natural:: BWO      = Plan64;
        const char * const Natural:: CallSign = "apn";
        Y_Shallow_Impl(Hook);

      
        const char * Natural:: callSign() const noexcept { return CallSign; }


        Natural:: Natural() :
        SmartDev( new Device(sizeof(uint64_t), Device::SmallPlan[Ops]) ),
        Shielded()
        {

        }
        

        Natural:: Natural(const Natural &n) :
        SmartDev( new Device( *n.device ) ),
        Shielded()
        {

        }

        Natural:: Natural(const Hook_ &, Device * const dev) :
        SmartDev(dev),
        Shielded()
        {

        }


        size_t Natural:: serialize(OutputStream &fp) const
        {
            assert(device);
            Y_Lock(**this);
            return device->srz(fp);
        }

        Natural & Natural:: xch( Natural &n ) noexcept
        {
            CoerceSwap(device,n.device);
            return *this;
        }

        uint64_t Natural:: ls64() const   noexcept
        {
            Y_Lock(**this);
            return device->make<uint64_t>().data[0];
        }


        bool Natural:: isOdd() const noexcept
        {
            return 0 != (0x01 & device->api->lsb());
        }

        bool Natural:: isEven() const noexcept
        {
            return 0 == (0x01 & device->api->lsb());
        }

        size_t Natural:: bits() const noexcept
        {
            assert(device);
            return device->bits;
        }

        size_t Natural:: bytes() const noexcept
        {
            assert(device);
            return device->bytes;
        }


        const uint8_t * Natural:: data8() const noexcept
        {
            return device->make<uint8_t>().data;
        }


        void Natural:: ldz() noexcept
        {
            device->ldz( Coerce(device->bits), Device::SmallPlan[Ops] );
        }

        void Natural:: ld1() noexcept
        {
            device->ld1(Coerce(device->bits), Device::SmallPlan[Ops] );
        }

        Natural & Natural:: operator=( const Natural &n )
        {
            Natural tmp(n);
            return  xch(tmp);
        }


        Natural:: Natural(const natural_t n) :
        SmartDev( new Device(CopyOf,n) ),
        Shielded() 
        {
        }

        Natural & Natural:: operator=(const natural_t n) noexcept
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
            Y_Lock(*self);
            if( os.flags() & std::ios_base::hex )
                return os << self.hexString();
            else
                return os << self.decString();
        }


        

        Natural:: Natural(const TwoToThePowerOf_ &, const size_t n) :
        SmartDev(0),
        Shielded()
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


        Natural:: Natural(InputStream &fp, const char * const varName ) :
        SmartDev( Device::Load(fp,varName) ),
        Shielded()
        {

        }
        

    }

}

#include "y/random/bits.hpp"

namespace Yttrium
{
    namespace Apex
    {
        Natural:: Natural(Random::Bits &ran, const size_t numBits) :
        SmartDev(0),
        Shielded()
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
