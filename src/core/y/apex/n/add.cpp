
#include "y/apex/natural.hpp"
#include "y/apex/block/model.hpp"

namespace Yttrium
{
    namespace Apex
    {
        Natural Natural:: operator+() const
        {
            return Natural(*this);
        }

        Model * Natural:: Add(const Natural &lhs, const Natural &rhs)
        {
            return Model::Add(Ops,*lhs.code,*rhs.code);
        }

        Model * Natural:: Add(const Natural &lhs, const natural_t rhs)
        {
            return Model::Add(Ops,*lhs.code,rhs);
        }

        Model * Natural:: Add(const natural_t lhs, const Natural &rhs)
        {
            return Add(rhs,lhs);
        }

        void  Natural:: incr()
        {
            Natural res(Attach,Natural::Add(*this,1) );
            xch(res);
        }

        Natural & Natural:: operator++()
        {
            incr();
            return *this;
        }

        Natural Natural:: operator++(int)
        {
            const Natural saved = *this;
            incr();
            return saved;
        }


    }

}
