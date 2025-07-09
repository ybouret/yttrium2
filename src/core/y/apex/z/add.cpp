
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

        Integer Integer:: Add(const Integer &lhs, const integer_t rhs)
        {
            const SignType rhs_s = Sign::Of(rhs);
            switch( Sign::Pair(lhs.s,rhs_s) )
            {
                case Sign::ZZ: break; // => zero

                case Sign::ZN:
                case Sign::ZP:
                    return rhs;

                case Sign::NZ:
                case Sign::PZ:
                    return lhs;

                case Sign::PP: { const Natural sum = lhs.n + natural_t(rhs);  return Integer(Positive,sum); }
                case Sign::NN: { const Natural sum = lhs.n + natural_t(-rhs); return Integer(Negative,sum); }

                case Sign::PN: {
                    const natural_t abr(-rhs);
                    switch( Natural:: Compare(lhs.n,abr) )
                    {
                        case __Zero__: break; // => zero
                        case Positive: { const Natural dif = lhs.n - abr; return Integer(Positive,dif); }
                        case Negative: { const Natural dif = abr - lhs.n; return Integer(Negative,dif); }
                    }
                } break; // => zero

                case Sign::NP: {
                    const natural_t rrr(rhs);
                    switch( Natural:: Compare(lhs.n,rrr) )
                    {
                        case __Zero__: break; // => zero
                        case Positive: { const Natural dif = lhs.n - rrr; return Integer(Negative,dif); }
                        case Negative: { const Natural dif = rrr - lhs.n; return Integer(Positive,dif); }
                    }
                } break; // => zero
            }

            return Integer();
        }


        Integer Integer:: Add(const integer_t lhs, const Integer &rhs)
        {
            return Add(rhs,lhs);
        }

        
        Integer Integer:: Add(const Integer &lhs, const Natural &rhs)
        {
            switch(lhs.s)
            {
                case __Zero__: return rhs;
                case Positive: { const Natural sum = lhs.n + rhs; assert(sum>0); return Integer(Positive,sum); }
                case Negative:
                    break;
            }
            switch( Natural::Compare(lhs.n,rhs) )
            {
                case __Zero__: break;
                case Negative: { const Natural dif = rhs-lhs.n; return Integer(Positive,dif); }
                case Positive: { const Natural dif = lhs.n-rhs; return Integer(Negative,dif); }
            }
            return Integer();
        }

        Integer Integer:: Add(const Natural &lhs, const Integer &rhs)
        {
            return Add(rhs,lhs);
        }

    }

}

namespace Yttrium
{

    namespace Apex
    {
        Integer Integer:: operator+() const
        {
            return *this;
        }

        void Integer:: incr()
        {
            switch(s)
            {
                case __Zero__: ld1();            break;
                case Positive: Coerce(n).incr(); break;
                case Negative:
                    if(n.bits()<=1)
                    {
                        assert(-1==*this);
                        assert(1==n);
                        ldz();
                    }
                    else
                    {
                        Coerce(n).decr();
                        assert(n>0);
                    }
            }
        }

        Integer & Integer:: operator++()
        {
            incr();
            return *this;
        }

        Integer   Integer:: operator++(int)
        {
            const Integer saved = *this;
            incr();
            return saved;
        }

    }

}
