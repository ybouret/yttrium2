

#include "y/apex/natural.hpp"
#include "y/apex/block/model.hpp"

namespace Yttrium
{
    namespace Apex
    {


        Model * Natural:: Sub(const Natural &lhs, const Natural &rhs)
        {
            return Model::Sub(Ops,*lhs.code,*rhs.code);
        }

        Model * Natural:: Sub(const Natural &lhs, const natural_t rhs)
        {
            return Model::Sub(Ops,*lhs.code,rhs);
        }

        Model * Natural:: Sub(const natural_t lhs, const Natural &rhs)
        {
            return Model::Sub(Ops,lhs,*rhs.code);
        }

        void  Natural:: decr()
        {
            Natural res(Attach,Natural::Sub(*this,1) );
            xch(res);
        }

        Natural & Natural:: operator--()
        {
            decr();
            return *this;
        }

        Natural Natural:: operator--(int)
        {
            Natural saved = *this;
            decr();
            return saved;
        }


    }

}
