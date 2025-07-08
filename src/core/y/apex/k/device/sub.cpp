
#include "y/apex/k/device.hpp"
#include "y/system/exception.hpp"
#include <cerrno>
#include "y/pointer/auto.hpp"

namespace Yttrium
{
    namespace Apex
    {

        namespace
        {
            template <typename SMALL, typename LARGE>
            struct DeviceSub
            {
                static const PlanType SmallPlan = PlanType( IntegerLog2For<SMALL>::Value );
                static const unsigned SmallBits = sizeof(SMALL) << 3;

                static inline
                Device * Compute(const SMALL *       lw,
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
                    AutoPtr<Device> result = new Device(ln*sizeof(SMALL),SmallPlan);
                    {
                        Parcel<SMALL>  & parcel  = result->get<SMALL>();
                        {
                            SMALL *          d       = parcel.data;
                            CarryType        cr      = 0;

                            //--------------------------------------------------
                            //
                            // common size
                            //
                            //--------------------------------------------------
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

                            //--------------------------------------------------
                            //
                            // propagate carry
                            //
                            //--------------------------------------------------
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
                        }
                        parcel.size = ln;
                    }
                    result->fix();
                    return result.yield();
                }

                static inline
                Device * Compute(const Device &lhs,
                                 const Device &rhs)
                {
                    const Parcel<SMALL> & L = lhs.make<SMALL>();
                    const Parcel<SMALL> & R = rhs.make<SMALL>();
                    return Compute(L.data,L.size,R.data,R.size);
                }

                static inline
                Device * Compute(const Device &lhs,
                                 natural_t     rhs)
                {

                    const Parcel<SMALL> & L = lhs.make<SMALL>();
                    const Parcel<SMALL>   R(rhs);
                    return Compute(L.data,L.size,R.data,R.size);
                }

                static inline
                Device * Compute(natural_t     lhs,
                                 const Device &rhs)
                {
                    const Parcel<SMALL>   L(lhs);
                    const Parcel<SMALL> & R = rhs.make<SMALL>();
                    return Compute(L.data,L.size,R.data,R.size);
                }

            };
        }

#define Y_Apex_Device_Call() \
/**/    static  Proc const Table[NumOps] =\
/**/    {\
/**/        DeviceSub<uint8_t,uint16_t> ::Compute, \
/**/        DeviceSub<uint8_t,uint32_t> ::Compute, \
/**/        DeviceSub<uint8_t,uint64_t> ::Compute, \
/**/        DeviceSub<uint16_t,uint32_t>::Compute, \
/**/        DeviceSub<uint16_t,uint64_t>::Compute, \
/**/        DeviceSub<uint32_t,uint64_t>::Compute  \
/**/    };\
/**/    return Table[ops](lhs,rhs)

        Device * Device:: Sub(const Device  &lhs, const Device  &rhs, OpsMode ops)
        {
            typedef Device * (*Proc)(const Device &, const Device &);
            Y_Apex_Device_Call();
        }

        Device * Device:: Sub(const Device  &lhs, const natural_t rhs, OpsMode ops)
        {
            typedef Device * (*Proc)(const Device &, const natural_t);
            Y_Apex_Device_Call();
        }


        Device * Device:: Sub(const natural_t lhs, const Device  &rhs, OpsMode ops)
        {
            typedef Device * (*Proc)(const natural_t, const Device &);
            Y_Apex_Device_Call();
        }
    }

}

