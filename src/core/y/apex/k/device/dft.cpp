
#include "y/apex/k/device.hpp"
#include "y/apex/m/archon.hpp"
#include "y/dft/dft.hpp"
#include "y/core/utils.hpp"
#include "y/pointer/auto.hpp"
#include "y/exception.hpp"
#include "y/system/wall-time.hpp"

namespace Yttrium
{
    namespace Apex
    {

        typedef double          real_t;
        typedef Complex<real_t> cplx_t;

        static inline
        Device * DFT_Mul(const uint8_t * u, const size_t n,
                         const uint8_t * v, const size_t m)
        {
            static Archon &archon = Archon::Instance();
            assert(0!=u);
            assert(0!=v);
            if(n<=0||m<=0) return new Device(0,Plan8);

            assert(n>0);
            assert(m>0);

            //------------------------------------------------------------------
            //
            // find array sizes
            //
            //------------------------------------------------------------------
            size_t       nn = 1;
            unsigned     ns = 0;
            {
                const size_t mn  = Max(m,n);
                while(nn<mn)
                {
                    nn <<= 1; ++ns;
                }
            }
            const size_t nc = nn; // number of complexes
            nn <<= 1; ++ns;       // number of reals

            //------------------------------------------------------------------
            //
            // allocate device
            //
            //------------------------------------------------------------------
            const size_t    mpn = m+n;
            AutoPtr<Device> dev = new Device(mpn,Plan8);
            Y_WallTime_Mark(Device::ProbeMUL);

            //------------------------------------------------------------------
            //
            // allocate workspace for twice nn reals a.k.a nn complexes
            //
            //------------------------------------------------------------------
            ns += IntegerLog2For<cplx_t>::Value;
            void * const wksp = archon.query(ns);

            //void *   wksp[4096];
            real_t * const a = ((real_t *) wksp )-1;
            real_t * const b = a+nn;

            //------------------------------------------------------------------
            //
            // fill workspaces
            //
            //------------------------------------------------------------------
            for(size_t i=n,k=0;i>0;--i) a[i] = u[k++];
            for(size_t i=m,k=0;i>0;--i) b[i] = v[k++];

            //------------------------------------------------------------------
            //
            // transform
            //
            //------------------------------------------------------------------
            DFT::RealForward(a,b,nn);

            //------------------------------------------------------------------
            //
            // convolution
            //
            //------------------------------------------------------------------
            b[1] *= a[1];
            b[2] *= a[2];
            {
                cplx_t * za = (cplx_t*)wksp;
                cplx_t * zb = za+nc;
                for(size_t i=nc-1;i>0;--i)
                    *(++zb) *= *(++za);
            }

            //------------------------------------------------------------------
            //
            // transform
            //
            //------------------------------------------------------------------
            DFT::RealReverse(b,nn);

            //------------------------------------------------------------------
            //
            //
            // compute bytes
            //
            //
            //------------------------------------------------------------------
            uint8_t * r8 = ((uint8_t *)wksp)-1;
            double    cy = 0;
            {
                static const double RX  = 256.0;
                for(size_t j=nn;j>0;--j) {
                    const double t = floor( b[j]/nc+cy+0.5 );
                    cy=(unsigned long) (t*0.00390625);
                    //*(uint8_t *)&b[j] =
                    r8[j] = (uint8_t)(t-cy*RX);
                }
                assert(cy<RX);
            }

            //------------------------------------------------------------------
            //
            // transfer
            //
            //------------------------------------------------------------------
            {
                Parcel<uint8_t> &p = dev->make<uint8_t>();
                uint8_t *        w = p.data + (p.size = mpn);

                *(--w) = (uint8_t) cy;
                for(size_t j=1;j<mpn;++j)
                    *(--w) = r8[j]; //*(const uint8_t *) &b[j];
                assert(w==p.data);

                dev->fix();
            }

            //------------------------------------------------------------------
            //
            // free workspace and return
            //
            //------------------------------------------------------------------
            archon.store(ns,wksp);
            Y_WallTime_Gain(Device::ProbeMUL);
            return dev.yield();
        }



        Device * Device:: MulDFT(const Device &lhs, const Device &rhs)
        {
            const Parcel<uint8_t> &u = lhs.make<uint8_t>();
            const Parcel<uint8_t> &v = rhs.make<uint8_t>();
            return DFT_Mul(u.data,u.size,v.data,v.size);
        }

        Device * Device:: MulDFT(const Device &lhs,  natural_t rhs)
        {
            const Parcel<uint8_t> &u = lhs.make<uint8_t>();
            const Parcel<uint8_t>  v(rhs);
            return DFT_Mul(u.data,u.size,v.data,v.size);
        }


        static inline
        Device * DFT_SQR(const uint8_t * u, const size_t n)
        {
            static Archon &archon = Archon::Instance();
            assert(0!=u);
            if(n<=0) return new Device(0,Plan8);

            assert(n>0);

            //------------------------------------------------------------------
            //
            // find array sizes
            //
            //------------------------------------------------------------------
            size_t       nn = 1;
            unsigned     ns = 0;
            {
                const size_t mn  = n;
                while(nn<mn)
                {
                    nn <<= 1; ++ns;
                }
            }
            const size_t nc = nn; // number of complexes
            nn <<= 1; ++ns;       // number of reals

            //------------------------------------------------------------------
            //
            // allocate device
            //
            //------------------------------------------------------------------
            const size_t    mpn = n<<1;;
            AutoPtr<Device> dev = new Device(mpn,Plan8);
            Y_WallTime_Mark(Device::ProbeMUL);

            //------------------------------------------------------------------
            //
            // allocate workspace for   nn reals a.k.a nn complexes
            //
            //------------------------------------------------------------------
            ns += IntegerLog2For<real_t>::Value;
            void * const wksp = archon.query(ns);

            //void *   wksp[4096];
            real_t * const b = ((real_t *) wksp )-1;

            //------------------------------------------------------------------
            //
            // fill workspaces
            //
            //------------------------------------------------------------------
            for(size_t i=n,k=0;i>0;--i) b[i] = u[k++];

            //------------------------------------------------------------------
            //
            // transform
            //
            //------------------------------------------------------------------
            DFT::RealForward(b,nn);

            //------------------------------------------------------------------
            //
            // convolution
            //
            //------------------------------------------------------------------
            b[1] *= b[1];
            b[2] *= b[2];
            {
                cplx_t * zb = (cplx_t*)wksp;
                for(size_t i=nc-1;i>0;--i)
                {
                    ++zb;
                    *zb *= *zb;
                }
            }

            //------------------------------------------------------------------
            //
            // transform
            //
            //------------------------------------------------------------------
            DFT::RealReverse(b,nn);

            //------------------------------------------------------------------
            //
            //
            // compute bytes
            //
            //
            //------------------------------------------------------------------
            double    cy = 0;
            {
                static const double RX  = 256.0;
                for(size_t j=nn;j>0;--j) {
                    const double t = floor( b[j]/nc+cy+0.5 );
                    cy=(unsigned long) (t*0.00390625);
                    *(uint8_t *)&b[j] = (uint8_t)(t-cy*RX);
                }
                assert(cy<RX);
            }

            //------------------------------------------------------------------
            //
            // transfer
            //
            //------------------------------------------------------------------
            {
                Parcel<uint8_t> &p = dev->make<uint8_t>();
                uint8_t *        w = p.data + (p.size = mpn);

                *(--w) = (uint8_t) cy;
                for(size_t j=1;j<mpn;++j)
                    *(--w) = *(const uint8_t *) &b[j];
                assert(w==p.data);

                dev->fix();
            }

            //------------------------------------------------------------------
            //
            // free workspace and return
            //
            //------------------------------------------------------------------
            archon.store(ns,wksp);
            Y_WallTime_Gain(Device::ProbeMUL);
            return dev.yield();
        }


        Device * Device:: SqrDFT(const Device &lhs)
        {
            const Parcel<uint8_t> &u = lhs.make<uint8_t>();
            return DFT_SQR(u.data,u.size);
        }
    }


}

