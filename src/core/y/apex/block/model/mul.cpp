
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
            static const unsigned SmallBits = sizeof(SMALL) * 8;
            static inline
            Model * Compute(const SMALL * const a,
                            const size_t        p,
                            const SMALL *       b,
                            const size_t        q)
            {
                assert(0!=a);
                assert(0!=b);
                assert(p>0);
                assert(q>0);
                const size_t   n     = p+q;
                Model *        model = new Model(n*sizeof(SMALL),SmallView);
                {
                    Block<SMALL> & block = model->get<SMALL>();
                    {
                        SMALL *        product = block.data;
                        for(size_t j=q;j>0;--j,++product)
                        {
                            const LARGE B     = static_cast<LARGE>(*(b++));
                            LARGE       carry = 0;
                            for(size_t i=0;i<p;++i)
                            {
                                carry     += static_cast<LARGE>(product[i]) + static_cast<LARGE>(a[i]) * B;
                                product[i] = static_cast<SMALL>(carry);
                                carry >>= SmallBits;
                            }
                            product[p] =  static_cast<SMALL>(carry);
                        }
                    }
                    block.size = n;
                }
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

            static inline
            Model * Compute(const Model &lhs, natural_t rhs)
            {
                assert(SmallView==lhs.view);
                assert(lhs.bytes>0);
                assert(rhs>0);
                const Block<SMALL> & L  = lhs.get<SMALL>();
                size_t               nr = 0;
                const SMALL * const  pr = UFormatAs<SMALL>(rhs,nr); assert(nr>0);
                return Compute(L.data,L.size,pr,nr);
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
                case MulOps::Case11: return new Model(CopyOf,1);
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

        Model * Model:: Mul(const OpsMode ops, const Model &lhs, const natural_t rhs)
        {
            typedef Model * (*MulProc)(const Model&,natural_t);
            Y_Apex_Model_Mul_Table();
            const ViewType view = SmallView[ops];

            switch( MulOps::Get(lhs.bits,rhs) )
            {
                case MulOps::Case00:
                case MulOps::Case01:
                case MulOps::Case0N:
                case MulOps::Case10:
                case MulOps::CaseN0: return new Model(CopyOf,0);
                case MulOps::Case11: return new Model(CopyOf,1);
                case MulOps::Case1N: return new Model(CopyOf,rhs);
                case MulOps::CaseN1: return new Model(lhs,view);
                case MulOps::CaseNN:
                    break;
            }

            assert(lhs.bits>1);
            assert(rhs>1);

            AutoPtr<Model> lp,rp;
            Model        * L = & Coerce(lhs); if(view != L->view) { lp = (L=new Model(lhs,view) ); }
            assert(view==L->view);
            return MulTable[ops](*L,rhs);
        }

    }
}


