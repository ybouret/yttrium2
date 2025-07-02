
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

        Integer Integer:: Add(const Integer &lhs, const integer_t rhs)
        {
            const Integer _(rhs);
            return Add(lhs,_);
        }

        Integer Integer::Add(const integer_t lhs, const Integer &rhs)
        {
            return Add(rhs,lhs);
        }


        Integer Integer:: Add(const Integer &lhs, const Natural &rhs)
        {
            switch(lhs.s)
            {
                case __Zero__: break;
                case Positive:
                    if(rhs.bits() <= 0)
                    {
                        return lhs;
                    }
                    else
                    {
                        const Natural sum = lhs.n + rhs;
                        return Integer(sum);
                    }
                case Negative:
                    switch( Natural::Compare(lhs.n,rhs))
                    {
                        case Positive: { const Natural dif = lhs.n-rhs; return Integer(Negative,dif); }
                        case Negative: { const Natural dif = rhs-lhs.n; return Integer(Positive,dif); }
                        case __Zero__: return Integer();
                    }
            }
            return Integer(rhs);
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

        void  Integer:: incr()
        {
            //Natural res(Attach,Natural::Add(*this,1) );
            //xch(res);
        }

        Integer & Integer:: operator++()
        {
            incr();
            return *this;
        }

        Integer Integer:: operator++(int)
        {
            const Integer saved = *this;
            incr();
            return saved;
        }
    }

}

