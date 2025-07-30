#include "y/apex/k/device.hpp"
#include "y/apex/k/device/mulops.hpp"
#include "y/system/wall-time.hpp"

namespace Yttrium
{
    namespace Apex
    {

        uint64_t * Device:: ProbeMUL = 0;

        namespace
        {
            template <typename SMALL, typename LARGE>
            struct DeviceMul
            {
                static const PlanType SmallPlan = PlanType( IntegerLog2For<SMALL>::Value );
                static const unsigned SmallBits = sizeof(SMALL) * 8;

                static inline
                Device * Compute(const SMALL * const a,
                                 const size_t        p,
                                 const SMALL *       b,
                                 const size_t        q)
                {
                    assert(0!=a);
                    assert(0!=b);
                    assert(p>0);
                    assert(q>0);
                    const size_t   n      = p+q;
                    Device *       device = new Device(n*sizeof(SMALL),SmallPlan);
                    Y_WallTime_Mark(Device::ProbeMUL);
                    {
                        Parcel<SMALL> & block = device->get<SMALL>();
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
                    device->fix();
                    Y_WallTime_Gain(Device::ProbeMUL);
                    return device;
                }

                static inline
                Device * Compute(const Device &lhs, const Device &rhs)
                {
                    assert(lhs.bits>1);
                    assert(rhs.bits>1);
                    const Parcel<SMALL> &L = lhs.make<SMALL>();
                    const Parcel<SMALL> &R = rhs.make<SMALL>();
                    return Compute(L.data,L.size,R.data,R.size);
                }

                static inline
                Device * Compute(const Device &lhs, natural_t rhs)
                {
                    assert(lhs.bits>1);
                    assert(rhs>1);
                    const Parcel<SMALL> &L = lhs.make<SMALL>();
                    const Parcel<SMALL>  R(rhs);
                    return Compute(L.data,L.size,R.data,R.size);
                }

            };
        }



#define Y_Apex_Device_Call() \
/**/    static  Proc const Table[NumOps] =\
/**/    {\
/**/        DeviceMul<uint8_t,uint16_t> ::Compute, \
/**/        DeviceMul<uint8_t,uint32_t> ::Compute, \
/**/        DeviceMul<uint8_t,uint64_t> ::Compute, \
/**/        DeviceMul<uint16_t,uint32_t>::Compute, \
/**/        DeviceMul<uint16_t,uint64_t>::Compute, \
/**/        DeviceMul<uint32_t,uint64_t>::Compute  \
/**/    };\
/**/    return Table[ops](lhs,rhs)


        Device * Device:: Mul(const Device &lhs, const Device &rhs, OpsMode ops)
        {

            switch( MulOps::Get(lhs.bits,rhs.bits) )
            {
                case MulOps::Case00:
                case MulOps::Case01:
                case MulOps::Case10:
                case MulOps::Case0N:
                case MulOps::CaseN0:
                    return new Device(0,SmallPlan[ops]);
                case MulOps::Case11:
                    return new Device(CopyOf,1);
                case MulOps::Case1N: return new Device(rhs);
                case MulOps::CaseN1: return new Device(lhs);
                case MulOps::CaseNN:
                    break;
            }

            typedef Device * (*Proc)(const Device &, const Device &);
            Y_Apex_Device_Call();
        }

        Device * Device:: Mul(const Device &lhs, const natural_t rhs, OpsMode ops)
        {
            switch( MulOps::Get(lhs.bits,rhs) )
            {
                case MulOps::Case00:
                case MulOps::Case01:
                case MulOps::Case10:
                case MulOps::Case0N:
                case MulOps::CaseN0:
                    assert(lhs.bits==0||rhs==0);
                    return new Device(0,SmallPlan[ops]);

                case MulOps::Case11:
                    assert(1==lhs.bits && 1==rhs);
                    return new Device(CopyOf,1);

                case MulOps::Case1N: return new Device(CopyOf,rhs);
                case MulOps::CaseN1: return new Device(lhs);
                case MulOps::CaseNN:
                    break;
            }

            typedef Device * (*Proc)(const Device &, natural_t);
            Y_Apex_Device_Call();
        }


        

    }

}
