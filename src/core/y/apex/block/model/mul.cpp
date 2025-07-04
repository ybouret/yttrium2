
#include "y/apex/block/model.hpp"
#include "y/apex/m/format.hpp"
#include "y/pointer/auto.hpp"

namespace Yttrium
{
    namespace Apex
    {
        template <typename SMALL, typename LARGE>
        struct ModelMul
        {
            static const ViewType SmallView = ViewType( IntegerLog2For<SMALL>::Value );

            static inline
            Model * Compute(const SMALL * const a,
                            const size_t        n,
                            const SMALL * const b,
                            const size_t        m)
            {
                assert(0!=a);
                assert(0!=b);
                if(n<=0||m<=0) return new Model(0,SmallView);
            }

            static inline
            Model * Compute(const Model &lhs, const Model &rhs)
            {
                assert(SmallView==lhs.view);
                assert(SmallView==rhs.view);
                const Block<SMALL> & L = lhs.get<SMALL>();
                const Block<SMALL> & R = rhs.get<SMALL>();
                return Compute(L.data,L.size,R.data,R.size);
            }

        };


#define Y_Apex_Model_Mul_Table() \
static MulProc MulTable[Ops] = \
{\
Y_Apex_Model_Table(ModelMul,::Compute) \
}

        Model * Model:: Mul(const OpsMode ops, const Model &lhs, const Model &rhs)
        {
            typedef Model * (*MulProc)(const Model&, const Model&);
            Y_Apex_Model_Mul_Table();
            const ViewType view = SmallView[ops];
            AutoPtr<Model> lp,rp;
            Model        * L = & Coerce(lhs); if(view != L->view) { lp = (L=new Model(lhs,view) ); }
            Model        * R = & Coerce(rhs); if(view != R->view) { rp = (R=new Model(rhs,view) ); }
            assert(view==L->view);
            assert(view==R->view);
            return MulTable[ops](*L,*R);
        }

    }
}


