
#include "y/apex/integer.hpp"
#include "y/system/exception.hpp"
#include <cerrno>

namespace Yttrium
{

    namespace Apex
    {


        Integer Integer:: Div(const Integer &lhs, const Integer &rhs)
        {

            switch( Sign::Pair(lhs.s,rhs.s) )
            {
                case Sign::ZZ:
                case Sign::NZ:
                case Sign::PZ:
                    throw Libc::Exception(EDOM,"%s division by zero %s", CallSign, CallSign);

                case Sign::ZN:
                case Sign::ZP:
                    break; // zero

                case Sign::NN:
                case Sign::PP: { const Natural q = lhs.n/rhs.n; return Integer(q); }
                case Sign::NP:
                case Sign::PN: { const Natural q = lhs.n/rhs.n; return Integer(q).neg(); }
            }

            return Integer();
        }

        Integer Integer:: Div(const Integer &lhs, const integer_t rhs)
        {
            const SignType rhs_s = Sign::Of(rhs);

            switch( Sign::Pair(lhs.s,rhs_s) )
            {
                case Sign::ZZ:
                case Sign::NZ:
                case Sign::PZ:
                    throw Libc::Exception(EDOM,"%s division by zero integer", CallSign);

                case Sign::ZN:
                case Sign::ZP:
                    break; // zero

                case Sign::NN: { const Natural q = lhs.n/natural_t(-rhs); return Integer(q); }
                case Sign::PP: { const Natural q = lhs.n/natural_t(rhs);  return Integer(q); }
                case Sign::NP: { const Natural q = lhs.n/natural_t(rhs);  return Integer(q).neg(); }
                case Sign::PN: { const Natural q = lhs.n/natural_t(-rhs); return Integer(q).neg(); }
            }
            return Integer();
        }


        Integer Integer:: Div(const integer_t lhs, const Integer &rhs)
        {
            const SignType lhs_s = Sign::Of(lhs);
            switch( Sign::Pair(lhs_s,rhs.s) )
            {
                case Sign::ZZ:
                case Sign::NZ:
                case Sign::PZ:
                    throw Libc::Exception(EDOM,"integer division by zero %s", CallSign);

                case Sign::ZN:
                case Sign::ZP:
                    break; // zero

                case Sign::NN: { const Natural q = natural_t(-lhs)/rhs.n; return Integer(q); }
                case Sign::PP: { const Natural q = natural_t(lhs)/rhs.n;  return Integer(q); }
                case Sign::NP: { const Natural q = natural_t(-lhs)/rhs.n; return Integer(q).neg(); }
                case Sign::PN: { const Natural q = natural_t(lhs)/rhs.n;  return Integer(q).neg(); }
            }

            return Integer();
        }

        Integer Integer:: Div(const Integer &lhs, const Natural &rhs)
        {
            if(rhs.bits()<=0)
                throw Libc::Exception(EDOM,"%s division by zero %s",CallSign,Natural::CallSign);

            switch(lhs.s)
            {
                case __Zero__: break;
                case Positive: { const Natural q = lhs.n / rhs; return Integer(q); }
                case Negative: { const Natural q = lhs.n / rhs; return Integer(q).neg(); }
            }
            return __Zero__;
        }

        Integer Integer:: Div(const Natural &lhs, const Integer &rhs)
        {
            switch(rhs.s)
            {
                case __Zero__:
                    break;

                case Positive:
                    if(lhs.bits()<=0)
                        return Integer();
                    else
                    {
                        const Natural q = lhs/rhs.n; return Integer(q);
                    }

                case Negative:
                    if(lhs.bits()<=0)
                        return Integer();
                    else
                    {
                        const Natural q = lhs/rhs.n; return Integer(q).neg();
                    }

            }
            throw Libc::Exception(EDOM,"%s division by zero %s",Natural::CallSign,CallSign);
        }


    }

}

