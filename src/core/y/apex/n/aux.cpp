
#include "y/apex/natural.hpp"
#include "y/apex/block/model.hpp"
namespace Yttrium
{
    namespace Apex
    {
        Natural Natural:: sqrt() const
        {
#if 0
            if(s<=1) return s;
            T x0 = s >> 1 ;
            while(true) {
                const T x1 = (x0+s/x0)>>1;
                if(x1>=x0) break;
                x0 = x1;
            }
            return x0;
#endif

            if(code->bits<=1) return *this;
            const Natural s  = *this; assert(s>=2);
            Natural       x0 = s; x0.shr(); assert(x0>=1);
            std::cerr << "s=" << s << " => x0=" << x0 << std::endl;
            while(true)
            {
                assert(x0>=1);
                assert(s>=2);
                const Natural rho = s/x0;
                
                std::cerr << "rho is computed" << std::endl;
                std::cerr << "rho=" << rho << std::endl;
                std::cerr << "x0=" << x0 << ", s/x0=" << rho<< std::endl;
                Natural x1 = (x0+s/x0);
                std::cerr << "x1=" << x1 << std::endl;
                x1.shr();
                if( x1 >= x0 ) break;
                x0.xch(x1);
            }
            return x0;
        }
    }

}
