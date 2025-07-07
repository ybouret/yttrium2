
#include "y/apex/block/model.hpp"
#include "y/apex/m/format.hpp"
#include "y/pointer/auto.hpp"
#include "y/system/exception.hpp"
#include <cerrno>

namespace Yttrium
{
    namespace Apex
    {
        template <typename SMALL, typename LARGE>
        struct ModelSub
        {
            static const ViewType SmallView = ViewType( IntegerLog2For<SMALL>::Value );
            static const unsigned SmallBits = sizeof(SMALL) << 3;

            static inline
            Model * Compute_(const SMALL *       lw,
                             const size_t        ln,
                             const SMALL *       rw,
                             const size_t        rn)
            {
                typedef typename SignedSizeOf< sizeof(LARGE) >::Type CarryType;
                static const CarryType Radix     = CarryType(1) << SmallBits;
                assert( Good(lw,ln) );
                assert( Good(rw,rn) );

                if(rn>ln)
                    throw Libc::Exception(EDOM, "Apex::Sub(lhs<rhs) Level-1");
                AutoPtr<Model> result = new Model(ln*sizeof(SMALL),SmallView);
                {
                    Block<SMALL>  &block  = result->get<SMALL>();
                    SMALL *        d      = block.data;

                    CarryType        cr  = 0;

                    //----------------------------------------------------------
                    //
                    // common size
                    //
                    //----------------------------------------------------------
                    for(size_t i=rn;i>0;--i)
                    {
                        cr += static_cast<CarryType>( *(lw++) ) - static_cast<CarryType>( *(rw++) );
                        if(cr<0)
                        {
                            *(d++) = static_cast<SMALL>(cr+Radix);
                            cr     = -1;
                        }
                        else
                        {
                            *(d++)  = static_cast<SMALL>(cr);
                            cr      = 0;
                        }
                    }

                    //----------------------------------------------------------
                    //
                    // propagate carry
                    //
                    //----------------------------------------------------------
                    for(size_t i=ln-rn;i>0;--i)
                    {
                        cr += static_cast<CarryType>( *(lw++) );
                        if(cr<0)
                        {
                            *(d++)  = static_cast<SMALL>(cr+Radix);
                            cr      = -1;
                        }
                        else
                        {
                            *(d++)  = static_cast<SMALL>(cr);
                            cr      = 0;
                        }
                    }

                    if(cr<0)
                        throw Libc::Exception(EDOM, "Apex::Sub(lhs<rhs) Level-2");

                    block.size = ln;
                }
                result->update();
                return result.yield();
            }


            static inline Model * Compute(const Model &lhs, const Model &rhs)
            {
                const Block<SMALL> &l = lhs.get<SMALL>();
                const Block<SMALL> &r = rhs.get<SMALL>();
                return Compute_(l.data,l.size,r.data,r.size);
            }

            static inline Model * Compute(const Model &lhs, natural_t rhs)
            {
                const Block<SMALL> &l = lhs.get<SMALL>();
                size_t              nr = 0;
                const SMALL * const rw = UFormatAs<SMALL>(rhs,nr);
                return Compute_(l.data,l.size,rw,nr);
            }

            static inline Model * Compute(natural_t lhs, const Model &rhs)
            {
                size_t              nl = 0;
                const SMALL * const lw = UFormatAs<SMALL>(lhs,nl);
                const Block<SMALL> &r  = rhs.get<SMALL>();
                return Compute_(lw,nl,r.data,r.size);
            }

        };

#define Y_Apex_Model_Sub_Table() \
static SubProc SubTable[Ops] = \
{\
Y_Apex_Model_Table(ModelSub,::Compute) \
}



        Model * Model:: Sub(const OpsMode ops, const Model &lhs, const Model &rhs)
        {
            typedef Model * (*SubProc)(const Model &, const Model &);
            Y_Apex_Model_Sub_Table();
            const ViewType view = SmallView[ops];
            AutoPtr<Model> lp,rp;
            Model        * L = & Coerce(lhs); if(view != L->view) { lp = (L=new Model(lhs,view) ); }
            Model        * R = & Coerce(rhs); if(view != R->view) { rp = (R=new Model(rhs,view) ); }
            assert(view==L->view);
            assert(view==R->view);
            return SubTable[ops](*L,*R);
        }

        Model * Model:: Sub(const OpsMode ops, const Model &lhs, const natural_t rhs)
        {
            typedef Model * (*SubProc)(const Model &,natural_t);
            Y_Apex_Model_Sub_Table();
            const ViewType view = SmallView[ops];
            AutoPtr<Model> lp,rp;
            Model        * L = & Coerce(lhs); if(view != L->view) { lp = (L=new Model(lhs,view) ); }
            assert(view==L->view);
            return SubTable[ops](*L,rhs);
        }


        Model * Model:: Sub(const OpsMode ops, const natural_t lhs, const Model &rhs)
        {
            typedef Model * (*SubProc)(natural_t, const Model &);
            Y_Apex_Model_Sub_Table();
            const ViewType view = SmallView[ops];
            AutoPtr<Model> rp;
            Model        * R = & Coerce(rhs); if(view != R->view) { rp = (R=new Model(rhs,view) ); }
            assert(view==R->view);
            return SubTable[ops](lhs,*R);
        }

    }

}

