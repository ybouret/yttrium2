
#include "y/apex/integer.hpp"

namespace Yttrium
{

    namespace Apex
    {



        Integer Integer:: Add(const Integer &lhs, const Integer &rhs)
        {

            switch( Sign::Pair(lhs.s,rhs.s) )
            {
                case Sign::ZZ: break; // => zero

                case Sign::ZN:
                case Sign::ZP:
                    return rhs;

                case Sign::NZ:
                case Sign::PZ:
                    return lhs;

                case Sign::PP: { const Natural sum = lhs.n + rhs.n; return Integer(Positive,sum); }
                case Sign::NN: { const Natural sum = lhs.n + rhs.n; return Integer(Negative,sum); }

                case Sign::PN:
                    switch( Natural:: Compare(lhs.n,rhs.n) )
                    {
                        case __Zero__: break; // => zero
                        case Positive: { const Natural dif = lhs.n - rhs.n; return Integer(Positive,dif); }
                        case Negative: { const Natural dif = rhs.n - lhs.n; return Integer(Negative,dif); }
                    }
                    break; // => zero

                case Sign::NP:
                    switch( Natural:: Compare(lhs.n,rhs.n) )
                    {
                        case __Zero__: break; // => zero
                        case Positive: { const Natural dif = lhs.n - rhs.n; return Integer(Negative,dif); }
                        case Negative: { const Natural dif = rhs.n - lhs.n; return Integer(Positive,dif); }
                    }
                    break; // => zero
            }

            return Integer();
        }
    }

}
