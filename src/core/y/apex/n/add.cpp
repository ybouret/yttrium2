
#include "y/apex/natural.hpp"
#include "y/apex/block/model.hpp"
#include "y/pointer/auto.hpp"

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
            const ViewType view = Model::SmallView[Ops];
            AutoPtr<Model> lp,rp;
            Model * L = Coerce(lhs.code); if(view!=L->view) { L = new Model(*L,view); lp = L; }
            Model * R = Coerce(rhs.code); if(view!=R->view) { R = new Model(*R,view); rp = R; }
            return Model::Add(Ops,*L,*R);
        }

        Model * Natural:: Add(const Natural &lhs, const natural_t rhs)
        {
            const ViewType view = Model::SmallView[Ops];
            AutoPtr<Model> lp;
            Model * L = Coerce(lhs.code); if(view!=L->view) { L = new Model(*L,view); lp = L; }
            return Model::Add(Ops,*L,rhs);
        }

        Model * Natural:: Add(const natural_t lhs, const Natural &rhs)
        {
            return Add(rhs,lhs);
        }

        void  Natural:: incr()
        {
            Natural res( Natural::Add(*this,1) );
            xch(res);
        }

        Natural & Natural:: operator++()
        {
            incr();
            return *this;
        }

        Natural Natural:: operator++(int)
        {
            Natural saved = *this;
            incr();
            return saved;
        }


    }

}
