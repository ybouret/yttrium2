
#include "y/apex/integer.hpp"

namespace Yttrium
{

    namespace Apex
    {


        Integer Integer:: Mul(const Integer &lhs, const Integer &rhs)
        {
            switch( Sign::Pair(lhs.s,rhs.s) )
            {
                case Sign::ZZ:
                case Sign::ZN:
                case Sign::ZP:
                case Sign::NZ:
                case Sign::PZ:
                    break;

                case Sign::NN:
                case Sign::PP: { const Natural p = lhs.n * rhs.n; return Integer(Positive,p); }
                case Sign::NP:
                case Sign::PN: { const Natural p = lhs.n * rhs.n; return Integer(Negative,p); }
            }
            
            return Integer();
        }


        Integer Integer:: Mul(const Integer &lhs, const integer_t rhs)
        {
            const SignType rhs_s = Sign::Of(rhs);
            switch( Sign::Pair(lhs.s,rhs_s) )
            {
                case Sign::ZZ:
                case Sign::ZN:
                case Sign::ZP:
                case Sign::NZ:
                case Sign::PZ:
                    break;

                case Sign::NN: { const Natural p = lhs.n * natural_t(-rhs); return Integer(Positive,p); }
                case Sign::PP: { const Natural p = lhs.n * natural_t(rhs);  return Integer(Positive,p); }
                case Sign::NP: { const Natural p = lhs.n * natural_t(rhs);  return Integer(Negative,p); }
                case Sign::PN: { const Natural p = lhs.n * natural_t(-rhs); return Integer(Negative,p); }
            }

            return Integer();
        }

        Integer Integer:: Mul(const integer_t lhs, const Integer &rhs)
        {
            return Mul(rhs,lhs);
        }

        Integer Integer:: Mul(const Integer &lhs, const Natural &rhs)
        {
            switch(lhs.s)
            {
                case __Zero__:
                    return Integer();

                case Positive:
                case Negative:
                    if(rhs.bits()<=0) return Integer();
                    break;
            }
            assert(rhs>0);
            Integer res(lhs);
            Coerce(res.n) *= rhs;
            return res;
        }

        Integer Integer:: Mul(const Natural &lhs, const Integer &rhs)
        {
            return Mul(rhs,lhs);
        }

    }

}
