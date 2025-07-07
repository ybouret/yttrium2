
#include "y/apex/natural.hpp"
#include "y/apex/k/device.hpp"

namespace Yttrium
{
    namespace Apex
    {

        SignType Natural:: Compare(const Natural &lhs, const Natural &rhs) noexcept
        {
            Y_Lock(lhs.seal);
            Y_Lock(rhs.seal);
            return Device::Compare(*lhs.device,*rhs.device,Cmp);
        }


        SignType Natural:: Compare(const Natural &lhs, const natural_t rhs) noexcept
        {
            Y_Lock(lhs.seal);
            return Device::Compare(*lhs.device,rhs,Cmp);
        }

        SignType Natural:: Compare(const natural_t lhs, const Natural &rhs) noexcept
        {
            Y_Lock(rhs.seal);
            return Device::Compare(lhs,*rhs.device,Cmp);
        }


    }

}

