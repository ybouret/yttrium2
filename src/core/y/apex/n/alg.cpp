#include "y/apex/natural.hpp"
#include "y/apex/k/device.hpp"

namespace Yttrium
{
    namespace Apex
    {
        Natural Natural:: abs() const
        {
            return *this;
        }

        void Natural:: shr() noexcept
        {
            device->set(BWO);
            device->shr();
        }

        Natural Natural:: sqrt() const
        {
            if(device->bits<=1) return *this;
            const Natural s  = *this; assert(s>=2);
            Natural       x0 = s; x0.shr(); assert(x0>=1);
            while(true)
            {
                assert(x0>=1);
                assert(s>=2);
                const Natural rho = s/x0;
                Natural x1 = (x0+s/x0);
                x1.shr();
                if( x1 >= x0 ) break; // TODO better
                x0.xch(x1);
            }
            return x0;
        }
    }

}

