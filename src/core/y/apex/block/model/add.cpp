#include "y/apex/block/model.hpp"
#include "y/apex/m/format.hpp"

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
                Model * const result  = new Model(nbig+1,SmallView);
                LARGE         carry   = 0;
                SMALL *       sum     = result->get<SMALL>().data;
                for(size_t i=nlit;i>0;--i)
                {
                    carry += LARGE( *(lit++) ) + LARGE( *(big++) );
                    *(sum)++ = SMALL(carry);
                    carry >>= SmallBits;
                }

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
                if(n<=0)
                {
                    if(m<=0)
                    {
                        return new Model(0,SmallView);
                    }
                    else
                    {
                        assert(0==n);
                        assert(m>0);
                        return new Model(b,m,SmallView);
                    }
                }
                else
                {
                    assert(n>0);
                    if(m<=0)
                    {
                        return new Model(a,n,SmallView);
                    }
                    else
                    {
                        return n<=m ? Compute_(a,n,b,m) : Compute_(b,m,a,n);
                    }
                }
            }

            static inline
            Model * Compute( Model &lhs, Model &rhs )
            {
                Block<SMALL> & L = lhs.make<SMALL>();
                Block<SMALL> & R = rhs.make<SMALL>();
                return Compute(L.data,L.size,R.data,R.size);
            }

            static inline
            Model * Compute( Model &lhs, natural_t rhs)
            {
                Block<SMALL> &      L = lhs.make<SMALL>();
                size_t              N = 0;
                const SMALL * const R = UFormatAs<SMALL>(rhs,N);
                return Compute(L.data,L.size,R,N);
            }


        };


#define Y_Apex_Model_Add_Table() \
static AddProc AddTable[Ops] = \
{\
 Y_Apex_Model_Table(ModelAdd,::Compute) \
};\
return AddTable[ops](lhs,rhs)


        Model * Model:: Add(const OpsMode &ops, Model &lhs, Model &rhs)
        {
            typedef Model * (*AddProc)(Model&,Model&);
            Y_Apex_Model_Add_Table();
        }

        Model * Model:: Add(const OpsMode &ops, Model &lhs, const natural_t rhs)
        {
            typedef Model * (*AddProc)(Model&,natural_t rhs);
            Y_Apex_Model_Add_Table();
        }


    }
}
