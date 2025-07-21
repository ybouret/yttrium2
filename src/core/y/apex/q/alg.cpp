
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

        Rational Rational:: sqr() const
        {
            const Integer n2 = numer.sqr();
            const Natural d2 = denom.sqr();
            return Rational(n2,d2);
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

            const Rational & q = *this;
            const Natural  & D = denom;
            const Natural  & N = numer.n;
            Natural          a = N;
            Natural          b = D;

            //while(true)
            for(size_t i=0;i<10;++i)
            {
                Natural newB = b * a * D;
                Natural newA = D*a.sqr() + N * b.sqr();
                newA.shr();
                Natural::Simplify(newA,newB);
                const Rational s(Positive,newA,newB);
                //std::cerr << "s=" << s << std::endl;
                const Rational s2 = s.sqr();

                if(s2 <= q )
                {
                    std::cerr << s2 <<  " <= " << q << std::endl;
                    const Rational sp12 = (s+1).sqr();
                    if(q<sp12)
                    {
                        std::cerr << q <<  " < " << sp12 << std::endl;
                        return s;
                    }
                }


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
