#include "y/dft/dft.hpp"
#include "y/utest/run.hpp"
#include "y/format/hexadecimal.hpp"
#include "y/random/mt19937.hpp"
#include "y/memory/stealth.hpp"
#include "y/calculus/bytes-for.hpp"
#include "y/core/utils.hpp"
#include "y/container/cxx/array.hpp"

using namespace Yttrium;

namespace
{
    static inline void fill8(uint8_t * p, uint64_t w, size_t n)
    {
        assert(n<=4);
        p += n;
        while(n-- > 0)
        {
            *(--p) = uint8_t(w);
            w >>= 8;
        }
    }

    static inline uint64_t read8(const uint8_t *p, size_t n)
    {
        assert(n<=8);
        uint64_t w = 0;
        while(n-- > 0)
        {
            w <<= 8;
            w |= *(p++);
        }
        return w;

    }


    static inline
    void dftmul(uint8_t       w[],
                const uint8_t u[],
                const size_t  n,
                const uint8_t v[],
                const size_t  m)
    {
        const size_t mn = Max(m,n);
        size_t       nn = 1;
        size_t       ns = 0;
        while (nn < mn)
        {
            nn <<= 1; ++ns;
        }
        const size_t nc = nn;
        nn <<= 1; ++ns;

        Y_ASSERT( size_t(1) << ns == nn);

        CxxArray<double> a(nn);
        CxxArray<double> b(nn);

        for(size_t i=n;i>0;--i) a[i] = u[i];
        for(size_t i=m;i>0;--i) b[i] = v[i];



#if 0
        DFT::RealForward(a()-1,nn);
        DFT::RealForward(b()-1,nn);
#else
        DFT::RealForward(a()-1, b()-1, nn);
#endif

        b[1] *= a[1];
        b[2] *= a[2];
        {
            Complex<double> * zb = (Complex<double> *) b();
            Complex<double> * za = (Complex<double> *) a();
            for(size_t i=nc-1;i>0;--i)
            {
                *(++zb) *= *(++za);
            }
        }




        DFT::RealReverse(b()-1,nn);
        double       cy  = 0;
        const double RX  = 256.0;
        for(size_t j=nn;j>0;--j) {
            const double t = floor( b[j]/nc+cy+0.5 );
            cy=(unsigned long) (t*0.00390625);
            *(uint8_t *)&b[j]= (uint8_t)(t-cy*RX);
        }

        if (cy >= RX)
        {
            throw Exception("cannot happen in dftmul");
        }

        w[1]=(uint8_t) cy;
        for(size_t j=2;j<=n+m;++j)
            w[j]=*(const uint8_t *) &b[j-1];

    }

}

Y_UTEST(dft_mul)
{

    Random::MT19937 ran;

    uint8_t u0[4] = { 0,0,0,0 };
    uint8_t v0[4] = { 0,0,0,0 };
    uint8_t w0[8] = { 0,0,0,0,0,0,0,0 };

    uint8_t * const u = Memory::Stealth::Cast<uint8_t>(u0) - 1;
    uint8_t * const v = Memory::Stealth::Cast<uint8_t>(v0) - 1;
    uint8_t * const w = Memory::Stealth::Cast<uint8_t>(w0) - 1;

    for(size_t ubits=0;ubits<=32;++ubits)
        for(size_t vbits=0;vbits<=32;++vbits)
            for(size_t iter=0;iter<32;++iter)
            {
                Y_Memory_BZero(u0);
                Y_Memory_BZero(v0);
                Y_Memory_BZero(w0);
                const uint64_t u64 = ran.to<uint32_t>(ubits);
                const uint64_t v64 = ran.to<uint32_t>(vbits);
                const uint64_t w64 = u64*v64;
                const size_t   n   = BytesFor(u64);
                const size_t   m   = BytesFor(v64);
                fill8(u0,u64,n);  Y_ASSERT(read8(u0,n) == u64);
                fill8(v0,v64,m);  Y_ASSERT(read8(v0,m) == v64);
                Hexadecimal::Display(std::cerr << "u64=" << Hexadecimal(u64,Concise) << " => ",u0,n) << " = " << u64 << std::endl;
                Hexadecimal::Display(std::cerr << "v64=" << Hexadecimal(v64,Concise) << " => ",v0,m) << " = " << v64 << std::endl;

                dftmul(w,u,n,v,m);

                Hexadecimal::Display(std::cerr << "w64=" << Hexadecimal(w64,Concise) << " => ",w0,n+m) << " = " << w64 << std::endl;
                Y_ASSERT(read8(w0,n+m) == w64);
            }


}
Y_UDONE()

