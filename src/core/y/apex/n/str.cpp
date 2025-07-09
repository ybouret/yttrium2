
#include "y/apex/natural.hpp"
#include "y/apex/k/device.hpp"

namespace Yttrium
{
    namespace Apex
    {
        String Natural:: hexString() const
        {
            return device->hex();
        }

        String Natural:: decString() const
        {
            const Natural ten = 10;
            Natural       n   = (*this);
            String        s;

            do
            {
                Natural q,r; Div_(&q, &r, n,ten);
                assert(r<ten);
                s += char('0'+r.ls64());
                n.xch(q);
            }
            while(n.device->bits>0);

            return s.reverse();
        }

    }
    
}
