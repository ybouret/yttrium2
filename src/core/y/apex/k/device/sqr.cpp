
#include "y/apex/k/device.hpp"
#include "y/system/wall-time.hpp"

namespace Yttrium
{
    namespace Apex
    {

        namespace
        {
            template <typename SMALL, typename LARGE>
            struct DeviceSqr
            {
                static const PlanType SmallPlan = PlanType( IntegerLog2For<SMALL>::Value );
                static const unsigned SmallBits = sizeof(SMALL) * 8;

                static inline
                Device * Compute(const SMALL * const a,
                                 const size_t        p)
                {
                    assert(0!=a);
                    assert(p>0);
                    const SMALL *  b      = a;
                    const size_t   q      = p;
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
                Device * Compute(const Device &dev)
                {
                    assert(dev.bits>1);
                    const Parcel<SMALL> &D = dev.make<SMALL>();
                    return Compute(D.data,D.size);
                }

            };


        }

#define Y_Apex_Device_Call() \
/**/    static  Proc const Table[NumOps] =\
/**/    {\
/**/        DeviceSqr<uint8_t,uint16_t> ::Compute, \
/**/        DeviceSqr<uint8_t,uint32_t> ::Compute, \
/**/        DeviceSqr<uint8_t,uint64_t> ::Compute, \
/**/        DeviceSqr<uint16_t,uint32_t>::Compute, \
/**/        DeviceSqr<uint16_t,uint64_t>::Compute, \
/**/        DeviceSqr<uint32_t,uint64_t>::Compute  \
/**/    };\
/**/    return Table[ops](dev)

        Device * Device:: Sqr(const Device &dev, OpsMode ops)
        {

            switch(dev.bits)
            {
                case 0: return new Device(0,SmallPlan[ops]);
                case 1: return new Device(CopyOf,1);
                default:
                    break;
            }

            typedef Device * (*Proc)(const Device &);
            Y_Apex_Device_Call();
        }
    }

}

