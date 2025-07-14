
#include "y/apex/k/device.hpp"

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

            };

        }

    }

}

