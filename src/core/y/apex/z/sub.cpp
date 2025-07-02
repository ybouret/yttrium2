
#include "y/apex/integer.hpp"

namespace Yttrium
{
    namespace Apex
    {
        Integer Integer:: Sub(const Integer &lhs, const Integer &rhs)
        {
            switch( Sign::Pair(lhs.s, rhs.s) )
            {
                case Sign::ZZ:
                    break; // ==> zero

                case Sign::ZP:
                case Sign::ZN:
                    return -rhs;

                case Sign::PZ:
                case Sign::NZ:
                    return lhs;

                case Sign::PN: { const Natural sum = lhs.n + rhs.n; return Integer(Positive,sum); }
                case Sign::NP: { const Natural sum = lhs.n + rhs.n; return Integer(Negative,sum); }

                case Sign::PP:
                    switch( Natural::Compare(lhs.n,rhs.n) )
                    {
                        case __Zero__: break; // ==> zero
                        case Positive: { const Natural dif = lhs.n-rhs.n; return Integer(Positive,dif); }
                        case Negative: { const Natural dif = rhs.n-lhs.n; return Integer(Negative,dif); }
                    }
                    break;

                case Sign::NN:
                    switch( Natural::Compare(lhs.n,rhs.n) )
                    {
                        case __Zero__: break; // ==> zero
                        case Positive: { const Natural dif = lhs.n-rhs.n; return Integer(Negative,dif); }
                        case Negative: { const Natural dif = rhs.n-lhs.n; return Integer(Positive,dif); }
                    }
                    break;
            }
            return Integer();
        }
    }

}


namespace Yttrium
{
    namespace Apex
    {
        Integer Integer:: operator-() const
        {
            return Integer( Sign::Opposite(s), n );
        }

        void  Integer:: decr()
        {
            //Natural res(Attach,Natural::Sub(*this,1) );
            //xch(res);
        }

        Integer & Integer:: operator--()
        {
            decr();
            return *this;
        }

        Integer Integer:: operator--(int)
        {
            const Integer saved = *this;
            decr();
            return saved;
        }

    }

}


