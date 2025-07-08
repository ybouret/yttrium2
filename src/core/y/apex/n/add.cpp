
#include "y/apex/natural.hpp"
#include "y/apex/k/device.hpp"

namespace Yttrium
{
    namespace Apex
    {

        Device * Natural:: Add(const Natural &lhs, const Natural &rhs)
        {
            Y_Lock(*lhs);
            Y_Lock(*rhs);
            return Device::Add(*lhs.device,*rhs.device,Ops);
        }


        Device * Natural:: Add(const Natural &lhs, const natural_t rhs)
        {
            Y_Lock(*lhs);
            return Device::Add(*lhs.device,rhs,Ops);
        }

        Device * Natural:: Add(const natural_t lhs, const Natural &rhs)
        {
            Y_Lock(*rhs);
            return Device::Add(*rhs.device,lhs,Ops);
        }
    }

}

