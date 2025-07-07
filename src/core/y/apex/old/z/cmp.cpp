
#include "y/apex/integer.hpp"

namespace Yttrium
{
    namespace Apex
    {

        SignType Integer:: Compare(const Integer &lhs, const Integer &rhs)
        {
            switch( Sign::Pair(lhs.s,rhs.s) )
            {
                case Sign::NZ:
                case Sign::NP:
                case Sign::ZP:
                    return Negative;

                case Sign::ZZ: break;

                case Sign::ZN:
                case Sign::PN:
                case Sign::PZ:
                    return Positive;

                case Sign::PP: return Natural::Compare(lhs.n,rhs.n);
                case Sign::NN: return Natural::Compare(rhs.n,lhs.n);
            }
            return __Zero__;
        }


        SignType Integer:: Compare(const Integer &lhs, const integer_t rhs)
        {
            const SignType rhs_s = Sign::Of(rhs);
            switch( Sign::Pair(lhs.s,rhs_s) )
            {
                case Sign::NZ:
                case Sign::NP:
                case Sign::ZP:
                    return Negative;

                case Sign::ZZ: break;

                case Sign::ZN:
                case Sign::PN:
                case Sign::PZ:
                    return Positive;

                case Sign::PP: return Natural::Compare(lhs.n,natural_t(rhs));
                case Sign::NN: return Natural::Compare(natural_t(-rhs),lhs.n);
            }
            return __Zero__;
        }

        SignType Integer:: Compare(const integer_t lhs, const Integer &rhs)
        {
            return Sign::Opposite( Compare(rhs,lhs) );
        }

        SignType Integer:: Compare(const Integer & lhs, const Natural & rhs)
        {
            switch(lhs.s)
            {
                case Negative: return Negative;
                case __Zero__: break;
                case Positive: return Natural::Compare(lhs.n,rhs);
            }
            return rhs.bits() <= 0 ? __Zero__ : Negative;
        }


        SignType Integer:: Compare(const Natural & lhs, const Integer & rhs)
        {
            return Sign::Opposite( Compare(rhs,lhs) );
        }

    }

}

