
#include "y/apex/k/device.hpp"

namespace Yttrium
{
    namespace Apex
    {

        namespace
        {
            template <typename SMALL, typename LARGE>
            struct DeviceAdd
            {
                static const PlanType SmallPlan = PlanType( IntegerLog2For<SMALL>::Value );
                static const unsigned SmallBits = sizeof(SMALL) * 8;

                static inline
                Device * Compute_(const SMALL *  lit,
                                  const size_t   nlit,
                                  const SMALL *  big,
                                  const size_t   nbig)
                {
                    assert(nbig>=nlit);
                    assert(nlit>0);
                    assert(nbig>0);
                    assert(lit);
                    assert(big);
                    const size_t   output = nbig+1;
                    Device * const result = new Device(output*sizeof(SMALL),SmallPlan);
                    LARGE         carry   = 0;
                    Parcel<SMALL> &blk    = result->get<SMALL>(); assert(blk.maxi>=output);
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
                    result->fix();
                    return result;
                }


                static inline
                Device * Compute(const SMALL * const a,
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
                Device * Compute(const Device &lhs,
                                 const Device &rhs)
                {
                    assert(lhs.bits>0);
                    assert(rhs.bits>0);

                    const Parcel<SMALL> & L = lhs.make<SMALL>();
                    const Parcel<SMALL> & R = rhs.make<SMALL>();
                    return Compute(L.data,L.size,R.data,R.size);
                }

                static inline
                Device * Compute(const Device &lhs,
                                 natural_t     rhs)
                {
                    assert(lhs.bits>0);
                    assert(rhs>0);

                    const Parcel<SMALL> & L = lhs.make<SMALL>();
                    const Parcel<SMALL>   R(rhs);
                    return Compute(L.data,L.size,R.data,R.size);
                }


            };

        }


#define Y_Apex_Device_Call() \
/**/    static  Proc const Table[NumOps] =\
/**/    {\
/**/        DeviceAdd<uint8_t,uint16_t> ::Compute, \
/**/        DeviceAdd<uint8_t,uint32_t> ::Compute, \
/**/        DeviceAdd<uint8_t,uint64_t> ::Compute, \
/**/        DeviceAdd<uint16_t,uint32_t>::Compute, \
/**/        DeviceAdd<uint16_t,uint64_t>::Compute, \
/**/        DeviceAdd<uint32_t,uint64_t>::Compute  \
/**/    };\
/**/    return Table[ops](lhs,rhs)

        Device * Device:: Add(const Device &lhs, const Device &rhs, OpsMode ops)
        {

            if(lhs.bits<=0)
            {
                if(rhs.bits<=0)
                {
                    return new Device(0,SmallPlan[ops]);
                }
                else
                {
                    return new Device(rhs);
                }
            }
            else
            {
                if(rhs.bits<=0)
                {
                    return new Device(lhs);
                }
                else
                {
                    typedef Device * (*Proc)(const Device &, const Device &);
                    Y_Apex_Device_Call();
                }
            }
        }

        Device * Device:: Add(const Device &lhs, const natural_t rhs, OpsMode ops)
        {
            if(lhs.bits<=0)
            {
                // lhs is zero
                if(rhs<=0)
                {
                    // result is zero
                    return new Device(0,SmallPlan[ops]);
                }
                else
                {
                    // result is rhs
                     return new Device(CopyOf,rhs);
                }
            }
            else
            {
                // lhs is positive
                if(rhs<=0)
                {
                    // result is rhs
                    return new Device(lhs);
                }
                else
                {
                    typedef Device * (*Proc)(const Device &, natural_t);
                    Y_Apex_Device_Call();
                }
            }
        }

    }

}


