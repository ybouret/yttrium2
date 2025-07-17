
#include "y/apex/rational.hpp"
#include "y/system/exception.hpp"
#include <cerrno>

namespace Yttrium
{
    namespace Apex
    {
        Rational Rational:: abs() const
        {
            const Integer N = numer.abs();
            return Rational(N,denom);
        }

        Rational Rational:: sqrt() const
        {

            switch(numer.s)
            {
                case 0: return Rational();
                case Negative: throw Libc::Exception(EDOM,"sqrt of negative %s",CallSign);
                case Positive:
                    break;
            }

            const Natural &D = denom;
            const Natural &N = numer.n;
            Natural        a = N;
            Natural        b = D;

            for(size_t i=0;i<4;++i)
            {
                Natural newB = b * a * D;
                Natural newA = D*a.sqr() + N * b.sqr();
                newA.shr();
                Natural::Simplify(newA,newB);
                const Rational q(Positive,newA,newB);
                std::cerr << "s=" << q << std::endl;

                a.xch(newA);
                b.xch(newB);
            }

            return Rational();
        }

        void Rational:: shr()
        {
            if(__Zero__ == numer.s) return;
            Coerce(denom) += denom;
            simplify();
        }
    }

}
