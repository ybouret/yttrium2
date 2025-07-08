

#include "y/apex/natural.hpp"
#include "y/apex/k/device.hpp"

namespace Yttrium
{
    namespace Apex
    {

        Device * Natural:: Sub(const Natural &lhs, const Natural &rhs)
        {
            Y_Lock(*lhs);
            Y_Lock(*rhs);
            return Device::Sub(*lhs.device,*rhs.device,Ops);
        }


        Device * Natural:: Sub(const Natural &lhs, const natural_t rhs)
        {
            Y_Lock(*lhs);
            return Device::Sub(*lhs.device,rhs,Ops);
        }

        Device * Natural:: Sub(const natural_t lhs, const Natural &rhs)
        {
            Y_Lock(*rhs);
            return Device::Sub(lhs,*rhs.device,Ops);
        }

        void Natural:: decr()
        {
            static const natural_t one = 1;
            Device *dev = Device::Sub(*device,one,Ops);
            delete device;
            Coerce(device) = dev;
        }

        Natural & Natural:: operator--()
        {
            decr();
            return *this;
        }

        Natural   Natural:: operator--(int)
        {
            const Natural saved = *this;
            decr();
            return saved;
        }
    }

}

