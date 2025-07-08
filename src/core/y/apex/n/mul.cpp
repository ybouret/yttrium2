
#include "y/apex/natural.hpp"
#include "y/apex/k/device.hpp"

namespace Yttrium
{
    namespace Apex
    {

        Device * Natural:: Mul(const Natural &lhs, const Natural &rhs)
        {
            Y_Lock(*lhs);
            Y_Lock(*rhs);
            return Device::Mul(*lhs.device,*rhs.device,Ops);
        }

        Device * Natural:: Mul(const Natural &lhs, const natural_t rhs)
        {
            Y_Lock(*lhs);
            return Device::Mul(*lhs.device,rhs,Ops);
        }

        Device * Natural:: Mul(const natural_t lhs, const Natural &rhs)
        {
            Y_Lock(*rhs);
            return Device::Mul(*rhs.device,lhs,Ops);
        }
    }

}

