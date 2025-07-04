#include "y/apex/block/model.hpp"
#include "y/apex/m/format.hpp"
#include "y/pointer/auto.hpp"

namespace Yttrium
{
    namespace Apex
    {
        template <typename SMALL, typename LARGE>
        struct ModelAdd
        {
            static const ViewType SmallView = ViewType( IntegerLog2For<SMALL>::Value );
            static const unsigned SmallBits = sizeof(SMALL) * 8;

            static inline
            Model * Compute_(const SMALL *  lit,
                             const size_t   nlit,
                             const SMALL *  big,
                             const size_t   nbig)
            {
                assert(nbig>=nlit);
                assert(nlit>0);
                assert(nbig>0);
                assert(lit);
                assert(big);
                const size_t  output  = nbig+1;
                Model * const result  = new Model(output*sizeof(SMALL),SmallView);
                LARGE         carry   = 0;
                Block<SMALL> &blk     = result->get<SMALL>(); assert(blk.maxi>=output);
                SMALL *       sum     = blk.data;

                // common part
                for(size_t i=nlit;i>0;--i)
                {
                    carry   += LARGE( *(lit++) ) + LARGE( *(big++) );
                    *(sum)++ = SMALL(carry);
                    carry  >>= SmallBits;
                }

                // propagate carry to bigger part
                for(size_t i=nbig-nlit;i>0;--i)
                {
                    carry   += LARGE( *(big++) );
                    *(sum)++ = SMALL(carry);
                    carry >>= SmallBits;
                }

                // store carry in last word
                *sum     = SMALL(carry);

                // update created model
                blk.size = output;
                result->update();
                return result;
            }

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
                return (n<=m) ? Compute_(a,n,b,m) : Compute_(b,m,a,n);
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
                assert(rhs>0);
                assert(lhs.bytes>0);
                const Block<SMALL> & L = lhs.get<SMALL>();
                size_t               N = 0;
                const SMALL * const  R = UFormatAs<SMALL>(rhs,N);
                return Compute(L.data,L.size,R,N);
            }


        };


#define Y_Apex_Model_Add_Table() \
static AddProc AddTable[Ops] = \
{\
 Y_Apex_Model_Table(ModelAdd,::Compute) \
}
        


        Model * Model:: Add(const OpsMode ops, const Model &lhs, const Model &rhs)
        {
            typedef Model * (*AddProc)(const Model&, const Model&);
            Y_Apex_Model_Add_Table();
            const ViewType view = SmallView[ops];

            if(lhs.bytes<=0)
            {
                if(rhs.bytes<=0)
                {
                    return new Model(0,view);
                }
                else
                {
                    return new Model(rhs,view);
                }
            }
            else
            {
                if(rhs.bytes<=0)
                {
                    return new Model(lhs,view);
                }
                else
                {
                    AutoPtr<Model> lp,rp;
                    Model        * L = & Coerce(lhs); if(view != L->view) { lp = (L=new Model(lhs,view) ); }
                    Model        * R = & Coerce(rhs); if(view != R->view) { rp = (R=new Model(rhs,view) ); }
                    assert(view==L->view);
                    assert(view==R->view);
                    return AddTable[ops](*L,*R);
                }
            }
        }

        Model * Model:: Add(const OpsMode ops, const Model &lhs, const natural_t rhs)
        {
            typedef Model * (*AddProc)(const Model &,natural_t rhs);
            Y_Apex_Model_Add_Table();
            const ViewType view = SmallView[ops];
            if(lhs.bytes<=0)
            {
                return new Model(CopyOf,rhs);
            }
            else
            {
                if(rhs<=0)
                    return new Model(lhs,view);
                else
                {
                    AutoPtr<Model> lp;
                    Model        * L = & Coerce(lhs); if(view != L->view) { lp = (L=new Model(lhs,view) ); }
                    assert(view==L->view);
                    return AddTable[ops](*L,rhs);
                }
            }
        }


        

    }
}
