
#include "y/apex/block/model.hpp"
#include "y/apex/m/format.hpp"
#include "y/pointer/auto.hpp"
#include "y/apex/block/model/mulops.hpp"

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
                assert(n>0);
                assert(m>0);
                const size_t   p     = n+m;
                Model *        model = new Model(p,SmallView);
                Block<SMALL> & block = model->get<SMALL>();
                


                block.size = p;
                model->update();
                return model;
            }

            static inline
            Model * Compute(const Model &lhs, const Model &rhs)
            {
                assert(SmallView==lhs.view);
                assert(SmallView==rhs.view);
                assert(lhs.bytes>0);
                assert(rhs.bytes>0);
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

            switch( MulOps::Get(lhs.bits,rhs.bits) )
            {
                case MulOps::Case00:
                case MulOps::Case01:
                case MulOps::Case0N:
                case MulOps::Case10:
                case MulOps::CaseN0: return new Model(0,view);
                case MulOps::Case11: return new Model(1);
                case MulOps::Case1N: return new Model(rhs,view);
                case MulOps::CaseN1: return new Model(lhs,view);

                case MulOps::CaseNN:
                    break;
            }

            assert(lhs.bits>1);
            assert(lhs.bits>1);

            AutoPtr<Model> lp,rp;
            Model        * L = & Coerce(lhs); if(view != L->view) { lp = (L=new Model(lhs,view) ); }
            Model        * R = & Coerce(rhs); if(view != R->view) { rp = (R=new Model(rhs,view) ); }
            assert(view==L->view);
            assert(view==R->view);
            return MulTable[ops](*L,*R);
        }

    }
}


