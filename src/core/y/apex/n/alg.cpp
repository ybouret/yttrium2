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

        static inline
        Natural apnGreatestCommonDivisor(Natural a, Natural b)
        {
            assert(a>0);
            assert(b>0);
            switch( Natural::Compare(a,b) )
            {
                case Negative: a.xch(b); break;
                case __Zero__: return a;
                case Positive:
                    break;
            }
            assert(a>=b);
            while(b.bits()>0)
            {
                Natural r = Natural::Mod(a,b);
                a.xch(b);
                b.xch(r);
            }
            return a;
        }

        Natural Natural:: GCD(const Natural &a, const Natural &b)
        {
            if(a.device->bits<=0)
            {
                if(b.device->bits<=0)
                {
                    return 1;
                }
                else
                {
                    return b;
                }
            }
            else
            {
                assert(a>0);
                if(b.device->bits<=0)
                {
                    return a;
                }
                else
                {
                    assert(b>0);
                    return apnGreatestCommonDivisor(a,b);
                }
            }
        }

        void Natural:: Simplify(Natural &a, Natural &b)
        {
            const Natural g = GCD(a,b);
            if(g.device->bits>1)
            {
                Natural A = a/g;
                Natural B = b/g;
                A.xch(a);
                B.xch(b);
            }
        }

        Natural Natural:: Factorial(const size_t n)
        {
            if(n<=1)
                return 1;
            else
            {
                Natural f = 2;
                for(size_t i=3;i<=n;++i)
                    f *= i;
                return f;
            }
        }

        Natural Natural:: Comb(const size_t n, const size_t k)
        {
            assert(k<=n);
            return Factorial(n)/Factorial(k)/Factorial(n-k);
        }

    }

}

