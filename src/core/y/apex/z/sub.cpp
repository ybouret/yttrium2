
#include "y/apex/integer.hpp"

namespace Yttrium
{

    namespace Apex
    {

        Integer Integer:: operator-() const
        {
            Integer z(*this);
            return z.neg();
        }

        Integer Integer:: Sub(const Integer &lhs, const Integer &rhs)
        {

            switch( Sign::Pair(lhs.s,rhs.s) )
            {
                case Sign::ZZ: break; // zero

                case Sign::PZ:
                case Sign::NZ:
                    return lhs;

                case Sign::ZP:
                case Sign::ZN:
                    return -rhs;

                case Sign::NP: { const Natural sum = lhs.n + rhs.n; return Integer(Negative,sum); }
                case Sign::PN: { const Natural sum = lhs.n + rhs.n; return Integer(Positive,sum); }

                case Sign::PP:
                    switch( Natural::Compare(lhs.n,rhs.n) )
                    {
                        case __Zero__: break; // zero
                        case Positive: { const Natural dif = lhs.n - rhs.n; return Integer(Positive,dif); }
                        case Negative: { const Natural dif = rhs.n - lhs.n; return Integer(Negative,dif); }
                    }
                    break; // zero

                case Sign:: NN:
                    switch( Natural::Compare(lhs.n,rhs.n) )
                    {
                        case __Zero__: break; // zero
                        case Positive: { const Natural dif = lhs.n - rhs.n; return Integer(Negative,dif); }
                        case Negative: { const Natural dif = rhs.n - lhs.n; return Integer(Positive,dif); }
                    }
                    break; // zero
            }
            return Integer();
        }

        Integer Integer:: Sub(const Integer &lhs, const integer_t rhs)
        {
            return Add(lhs,-rhs);
        }


        Integer Integer:: Sub(const integer_t lhs, const Integer &rhs)
        {
            return Add(rhs,-lhs).neg();
        }

        Integer Integer:: Sub(const Integer &lhs, const Natural &rhs)
        {
            switch(lhs.s)
            {
                case __Zero__: return Integer(rhs).neg();
                case Negative: { Integer res(lhs); Coerce(res.n) += rhs; return res; }
                case Positive: break;
            }
            switch( Natural::Compare(lhs.n,rhs) )
            {
                case __Zero__: break;
                case Positive: { const Natural dif = lhs.n - rhs; return Integer(Positive,dif); }
                case Negative: { const Natural dif = rhs - lhs.n; return Integer(Negative,dif); }
            }
            return Integer();
        }

        Integer Integer:: Sub(const Natural &lhs, const Integer &rhs)
        {
            return Sub(rhs,lhs).neg();
        }

    }

}
