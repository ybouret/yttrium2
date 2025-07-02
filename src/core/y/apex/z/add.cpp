
#include "y/apex/integer.hpp"

namespace Yttrium
{
    namespace Apex
    {
        Integer Integer::Add(const Integer &lhs, const Integer &rhs)
        {
            switch( Sign::Pair(lhs.s, rhs.s) )
            {
                case Sign::ZZ:
                    break; // ==> zero

                case Sign::ZP:
                case Sign::ZN:
                    return rhs;

                case Sign::PZ:
                case Sign::NZ:
                    return lhs;

                case Sign::PP: { const Natural sum = lhs.n + rhs.n; return Integer(Positive,sum); }
                case Sign::NN: { const Natural sum = lhs.n + rhs.n; return Integer(Negative,sum); }

                case Sign::PN:
                    switch( Natural::Compare(lhs.n,rhs.n) )
                    {
                        case Positive: { const Natural dif = lhs.n-rhs.n; return Integer(Positive,dif); }
                        case Negative: { const Natural dif = rhs.n-lhs.n; return Integer(Negative,dif); }
                        case __Zero__:
                            break;
                    }
                    break; // ==> zero

                case Sign::NP:
                    switch( Natural::Compare(lhs.n,rhs.n) )
                    {
                        case Positive: { const Natural dif = lhs.n-rhs.n; return Integer(Negative,dif); }
                        case Negative: { const Natural dif = rhs.n-lhs.n; return Integer(Positive,dif); }
                        case __Zero__:
                            break;
                    }
                    break; // ==> zero

            }
            return Integer();
        }
    }

}
