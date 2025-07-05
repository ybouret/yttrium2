#include "y/apex/m/archon.hpp"
#include "y/apex/m/format.hpp"

#include "y/utest/run.hpp"
#include "y/random/park-miller.hpp"
#include "y/random/fill.hpp"
#include "y/format/hexadecimal.hpp"
#include "y/check/static.hpp"
#include <cstring>

using namespace Yttrium;

namespace Yttrium
{
    namespace Apex
    {
        enum PlanType
        {
            Plan8  = 0,
            Plan16 = 1,
            Plan32 = 3,
            Plan64 = 3
        };

#define Y_Apex_Parcel_Check(EXPR) \
do { if ( !(EXPR) ) { std::cerr << " *** '" << #EXPR << "' failure'" << std::endl; return false; } } while(false)

        class ParcelAPI
        {
        public:
            static const char * const HumanReadablePlan[Metrics::Views];

            explicit ParcelAPI(const size_t capa) noexcept :
            size(0),
            maxi(capa)
            {
            }

            virtual ~ParcelAPI() noexcept
            {
            }

            friend std::ostream & operator<<(std::ostream &os, const ParcelAPI &self)
            {
                return self.print(os);
            }

            bool sanity() const noexcept
            {
                Y_Apex_Parcel_Check(size<=maxi);
                return check();
            }

            virtual void   adjust()                     noexcept = 0;
            virtual void   resize(const size_t numBits) noexcept = 0;
            virtual size_t bits()                 const noexcept = 0;

            size_t       size; //!< size in words
            const size_t maxi; //!< capacity in words

        private:
            Y_Disable_Copy_And_Assign(ParcelAPI);
            virtual bool           check() const noexcept = 0;
            virtual std::ostream & print(std::ostream &os) const = 0;
        };


        template <typename T> class Parcel;



        template <typename T>
        class Parcel : public ParcelAPI
        {
        public:
            typedef T             Unit;
            static const size_t   BitsPerUnit = sizeof(Unit) * 8;
            static const PlanType Plan = PlanType( IntegerLog2For<T>::Value );

            //! build with block of memory
            inline explicit Parcel(void * const blockAddr,
                                   const size_t blockSize) noexcept :
            ParcelAPI(blockSize/sizeof(T)),
            data( static_cast<T*>(blockAddr) )
            {
                assert( 0 == (blockSize%sizeof(T)) );
                assert( maxi>0 );

            }

            //! local parcel
            inline explicit Parcel( uint64_t &qw ) noexcept :
            ParcelAPI( sizeof(uint64_t)/sizeof(T) ),
            data( UFormatAs<T>(qw,size) )
            {
                assert( sanity() );
            }


            inline virtual ~Parcel() noexcept
            {

            }

            inline virtual void adjust() noexcept
            {
                while(size>0 && 0 == data[size-1]) --size;
                assert(sanity());
            }

            inline virtual size_t bits() const noexcept
            {
                switch(size)
                {
                    case 0: return 0;
                    case 1: return Calculus::BitsFor::Count(data[0]);
                    default:
                        break;
                }
                assert(size>1);
                const size_t msi = size-1;
                return msi * BitsPerUnit + Calculus::BitsFor::Count(data[msi]);
            }

            inline virtual void resize(const size_t numBits) noexcept
            {
                size  = SizeFor<T>::From(numBits);
            }


            T * const data;
        private:
            Y_Disable_Copy_And_Assign(Parcel);
            inline virtual bool check() const noexcept
            {
                if(size>0)
                    Y_Apex_Parcel_Check(0!=data[size-1]);
                return true;
            }

            inline virtual std::ostream & print(std::ostream &os) const
            {
                os << HumanReadablePlan[Plan] << ":";
                if(size<=0) os << "[]";
                else
                {
                    size_t i=size;
                    while(i>0)
                        os << '[' << Hexadecimal(data[--i]).c_str()+2 << ']';
                }
                os << ":size=" << size;
                if(Plan!=Plan8) os << ":bytes=" << size * sizeof(T);
                return os;
            }
        };

        const char * const ParcelAPI:: HumanReadablePlan[Metrics::Views] =
        {
            "Plan8 ", "Plan16", "Plan32", "Plan64"
        };


        struct Transmute
        {

            //! Expand Parcels with synchronized size
            template <typename SMALL, typename LARGE> static inline
            void Expand(Parcel<SMALL>       &small,
                        const Parcel<LARGE> &large) noexcept
            {
                Y_STATIC_CHECK(sizeof(SMALL)<sizeof(LARGE),BadType);
                static const unsigned SmallBits = sizeof(SMALL)*8;
                SMALL *       tgt = small.data;
                const LARGE * src = large.data;
                for(size_t i=large.size;i>0;--i)
                {
                    LARGE value = *(src++);
                    for(size_t j=sizeof(LARGE)/sizeof(SMALL);j>0;--j, value>>=SmallBits)
                        *(tgt++) = SMALL(value);
                }

            }

            //! Shrink Parcels with synchronized size
            template <typename LARGE, typename SMALL> static inline
            void Shrink(Parcel<LARGE>       &large,
                        const Parcel<SMALL> &small) noexcept
            {
                Y_STATIC_CHECK(sizeof(SMALL)<sizeof(LARGE),BadType);
                static const unsigned SmallBits = sizeof(SMALL)*8;
                LARGE *       tgt = large.data;
                const SMALL * src = small.data;
                for(size_t i=large.size;i>0;--i)
                {
                    LARGE value = 0;
                    for(unsigned j=0;j<sizeof(LARGE)/sizeof(SMALL);++j)
                    {
                        LARGE tmp = *(src++);
                        tmp  <<= SmallBits*j;
                        value |=  tmp;
                    }
                    *(tgt)++ = value;
                }
            }

            template <typename SMALL, typename LARGE> static inline
            void To(Parcel<SMALL>       &      small,
                    const Parcel<LARGE> &      large,
                    const IntToType<Negative> &) noexcept
            {
                Expand(small,large);
            }

            template <typename T> static inline
            void To(Parcel<T>       & ,
                    const Parcel<T> & ,
                    const IntToType<__Zero__> &) noexcept
            {
            }

            template <typename LARGE, typename SMALL> static inline
            void To(Parcel<LARGE>       &      large,
                    const Parcel<SMALL> &      small,
                    const IntToType<Positive> &) noexcept
            {
                Shrink(large,small);
            }

            template <const unsigned lhs, const unsigned rhs>
            struct SignOf
            {
                static const SignType Value = (lhs<rhs) ? Negative : ( (rhs<lhs) ? Positive : __Zero__ );
            };


            template <typename TARGET, typename SOURCE> static inline
            void To(Parcel<TARGET>       & target,
                    const Parcel<SOURCE> & source) noexcept
            {
                static const IntToType< SignOf< sizeof(TARGET), sizeof(SOURCE) >::Value > choice = {};
                return To(target,source,choice);
            }


        };
    }

}

namespace
{
    template <typename T>
    static inline void testParcel(const Apex::Parcel<T> &p, const size_t numBits)
    {
        std::cerr << "\t" << p << std::endl;
        Y_ASSERT( p.bits() == numBits );
    }

    static
    bool is_little_endian() noexcept
    {
        static const uint8_t  byte[2]={0,1};
        const uint16_t        word = *(uint16_t*)(&(byte[0]));
        return 0x0100 == word;
    }

}

Y_UTEST(apex_parcel)
{
    Concurrent::Singulet::Verbose = true;

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


        }
    }

    std::cerr << "is_little_endian=" << is_little_endian() << std::endl;

}
Y_UDONE()

