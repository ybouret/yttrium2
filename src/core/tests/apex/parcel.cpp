#include "y/apex/k/parcel.hpp"
#include "y/apex/k/parcel/transmute.hpp"

#include "y/apex/m/archon.hpp"
#include "y/apex/m/format.hpp"


#include "y/utest/run.hpp"
#include "y/random/park-miller.hpp"
#include "y/random/fill.hpp"
#include "y/check/static.hpp"
#include <cstring>

using namespace Yttrium;

namespace
{
    template <typename T>
    static inline void testParcel(const Apex::Parcel<T> &p, const size_t numBits)
    {
        std::cerr << "\t" << p << std::endl;
        Y_ASSERT( p.bits() == numBits );
    }



}

Y_UTEST(apex_parcel)
{

    Y_SIZEOF(Apex::JMutex);
    Random::ParkMiller ran;

    for(size_t i=0;i<=64;++i)
    {
        const uint64_t u = ran.to<uint64_t>(i);
        std::cerr << Hexadecimal(u) << std::endl;
        {
            uint64_t qw = u;
            Apex::Parcel<uint8_t> p(qw);
            testParcel(p,i);

        }

        {
            uint64_t qw = u;
            Apex::Parcel<uint16_t> p(qw);
            testParcel(p,i);
        }

        {
            uint64_t qw = u;
            Apex::Parcel<uint32_t> p(qw);
            testParcel(p,i);
        }

        {
            uint64_t qw = u;
            Apex::Parcel<uint64_t> p(qw);
            testParcel(p,i);
        }
    }

    uint8_t      w8[16];
    uint16_t     w16[8];
    uint32_t     w32[4];
    uint64_t     w64[2];
    const size_t wlen = sizeof(w64);
    Apex::Parcel<uint8_t>  p8 (w8,wlen);  std::cerr << "p8 .maxi=" << p8.maxi << std::endl;
    Apex::Parcel<uint16_t> p16(w16,wlen); std::cerr << "p16.maxi=" << p16.maxi << std::endl;
    Apex::Parcel<uint32_t> p32(w32,wlen); std::cerr << "p32.maxi=" << p32.maxi << std::endl;
    Apex::Parcel<uint64_t> p64(w64,wlen); std::cerr << "p64.maxi=" << p64.maxi << std::endl;


    {
        for(size_t i=0;i<=128;++i)
        {
            Y_Memory_BZero(w64);
            if(i<=64)
            {
                w64[0] = ran.to<uint64_t>( i );

            }
            else
            {
                w64[0] = ran.to<uint64_t>();
                w64[1] = ran.to<uint64_t>(i-64);
            }

            const uint64_t org[2] = { w64[0], w64[1]};


            p64.size = p64.maxi;
            p64.adjust();
            Y_ASSERT(p64.sanity());
            std::cerr << p64 << std::endl;
            const size_t numBits = p64.bits(); assert(i==numBits);

            p8.resize(numBits);
            p16.resize(numBits);
            p32.resize(numBits);



            Y_Memory_BZero(w8);
            Apex::Transmute::To(p8,p64);
            Y_ASSERT(p8.sanity());
            Y_ASSERT(p8.bits() == numBits);
            std::cerr << p8 << std::endl;

            Y_Memory_BZero(w64);
            Apex::Transmute::To(p64,p8);
            Y_ASSERT(p64.sanity());
            Y_ASSERT(p64.bits() == numBits);
            Y_ASSERT(0==memcmp(p64.data,org,sizeof(org)));

            Y_Memory_BZero(w16);
            Apex::Transmute::To(p16,p64);
            Y_ASSERT(p16.sanity());
            Y_ASSERT(p16.bits() == numBits);
            std::cerr << p16 << std::endl;

            Y_Memory_BZero(w64);
            Apex::Transmute::To(p64,p16);
            Y_ASSERT(p64.sanity());
            Y_ASSERT(p64.bits() == numBits);
            Y_ASSERT(0==memcmp(p64.data,org,sizeof(org)));

            Y_Memory_BZero(w32);
            Apex::Transmute::To(p32,p64);
            Y_ASSERT(p32.sanity());
            Y_ASSERT(p32.bits() == numBits);
            std::cerr << p32 << std::endl;

            Y_Memory_BZero(w64);
            Apex::Transmute::To(p64,p32);
            Y_ASSERT(p64.sanity());
            Y_ASSERT(p64.bits() == numBits);
            Y_ASSERT(0==memcmp(p64.data,org,sizeof(org)));
        }
    }


    //Apex::Parcels ap(100,Apex::Plan8);


}
Y_UDONE()

