
#include "y/apex/integer.hpp"

namespace Yttrium
{

    namespace Apex
    {

        SignType Integer:: Compare(const Integer &lhs, const Integer &rhs) noexcept
        {

            switch( Sign::Pair(lhs.s,rhs.s) )
            {

                case Sign::NZ:
                case Sign::NP:
                case Sign::ZP:
                    return Negative;

                case Sign::ZN:
                case Sign::PZ:
                case Sign::PN:
                    return Positive;

                case Sign::PP: return Natural::Compare(lhs.n,rhs.n);
                case Sign::NN: return Natural::Compare(rhs.n,lhs.n);

                case Sign::ZZ:
                    break;
            }
            return __Zero__;
        }

        SignType Integer:: Compare(const Integer &lhs, const integer_t rhs) noexcept
        {
            const SignType rhs_s = Sign::Of(rhs);
            switch( Sign::Pair(lhs.s,rhs_s) )
            {

                case Sign::NZ:
                case Sign::NP:
                case Sign::ZP:
                    return Negative;

                case Sign::ZN:
                case Sign::PZ:
                case Sign::PN:
                    return Positive;

                case Sign::PP: return Natural::Compare(lhs.n,natural_t(rhs));
                case Sign::NN: return Natural::Compare(natural_t(-rhs),lhs.n);

                case Sign::ZZ:
                    break;
            }
            return __Zero__;
        }

        SignType Integer:: Compare(const integer_t lhs, const Integer &rhs) noexcept
        {
            return Sign::Opposite(Compare(rhs,lhs));
        }

        SignType Integer:: Compare(const Integer &lhs, const Natural &rhs) noexcept
        {
            if(lhs.s == Negative)
                return Negative;
            else
                return Natural::Compare(lhs.n,rhs);
        }

        SignType Integer:: Compare(const Natural &lhs, const Integer &rhs) noexcept
        {
            return Sign::Opposite( Compare(rhs,lhs) );
        }
    }

}

