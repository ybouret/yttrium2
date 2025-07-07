#include "y/apex/k/parcel/api.hpp"

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
                assert(sanity());
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

            virtual void naught(ParcelAPI * const sync[])  noexcept
            {
                assert(sanity());
                while(size>0) data[--size] = 0;
                assert(sanity());
                sync[0]->size = 0;
                sync[1]->size = 0;
                sync[2]->size = 0;
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

        template <PlanType> struct UIntFor;
        template <> struct UIntFor<Plan8>  { typedef uint8_t  Type; };
        template <> struct UIntFor<Plan16> { typedef uint16_t Type; };
        template <> struct UIntFor<Plan32> { typedef uint32_t Type; };
        template <> struct UIntFor<Plan64> { typedef uint64_t Type; };

        class Parcels
        {
        public:
            typedef Parcel<uint8_t> ParcelProto;
            static const unsigned   ParcelProtoSize = sizeof(ParcelProto);
            static const unsigned   ParcelProtoBytes = Metrics::Views * ParcelProtoSize;
            static const size_t     ParcelProtoWords = Alignment::WordsGEQ<ParcelProtoBytes>::Count;

            explicit Parcels(const size_t   userBlockSize,
                             const PlanType userBlockPlan) :
            addr(0),
            plan(userBlockPlan),
            pAPI(0),
            sync(),
            wksp(),
            blockShift(0),
            blockBytes(Metrics::BytesFor(userBlockSize,blockShift)),
            blockEntry( Query(blockShift) )
            {
                initialize();
            }

            explicit Parcels(const Parcels &other) :
            addr(0),
            plan(other.plan),
            pAPI(0),
            sync(),
            wksp(),
            blockShift(0),
            blockBytes(Metrics::BytesFor(other.room(),blockShift)),
            blockEntry( Query(blockShift) )
            {
                initialize();
                parcel<uint8_t>() .size = other.parcel<uint8_t>() .size;
                parcel<uint16_t>().size = other.parcel<uint16_t>().size;
                parcel<uint32_t>().size = other.parcel<uint32_t>().size;
                Parcel<uint64_t> &       target = parcel<uint64_t>();
                const Parcel<uint64_t> & source = other.parcel<uint64_t>();
                memcpy(target.data,source.data, (target.size=source.size) * sizeof(uint64_t) );
            }

            virtual ~Parcels() noexcept
            {
                static Archon & archon = Archon::Location();
                archon.store(blockShift,blockEntry);
            }

            // bytes to hold highest plan
            size_t room() const noexcept
            {
                return parcel<uint64_t>().size * sizeof(uint64_t);
            }


            void ldz(const PlanType userPlan) noexcept
            {
                pAPI->naught(sync[plan]);
                Coerce(plan) = userPlan;
                selectAPI();
            }



        private:
            Y_Disable_Assign(Parcels);
            uint8_t * const   addr;
        public:
            const PlanType    plan;
            ParcelAPI * const pAPI;

        private:
            ParcelAPI * const sync[Metrics::Views][Metrics::Views-1];
            void    *         wksp[ParcelProtoWords];
            unsigned          blockShift;
            const size_t      blockBytes;
            void * const      blockEntry;

            void selectAPI() noexcept
            {
                switch(plan)
                {
                    case Plan8:  Coerce(pAPI) = & parcel<uint8_t>();  break;
                    case Plan16: Coerce(pAPI) = & parcel<uint16_t>(); break;
                    case Plan32: Coerce(pAPI) = & parcel<uint32_t>(); break;
                    case Plan64: Coerce(pAPI) = & parcel<uint64_t>(); break;
                }
            }

            void initialize() noexcept
            {
                uint8_t * const p = ( Coerce(addr) = static_cast<uint8_t *>( Y_Memory_BZero(wksp) ) );
                new (p)                     Parcel<uint8_t>(blockEntry,blockBytes);
                new (p +   ParcelProtoSize) Parcel<uint16_t>(blockEntry,blockBytes);
                new (p + 2*ParcelProtoSize) Parcel<uint32_t>(blockEntry,blockBytes);
                new (p + 3*ParcelProtoSize) Parcel<uint64_t>(blockEntry,blockBytes);

                Coerce( sync[Plan8][0] ) = & parcel<uint16_t>();
                Coerce( sync[Plan8][1] ) = & parcel<uint32_t>();
                Coerce( sync[Plan8][2] ) = & parcel<uint64_t>();

                Coerce( sync[Plan16][0] ) = & parcel<uint8_t>();
                Coerce( sync[Plan16][1] ) = & parcel<uint32_t>();
                Coerce( sync[Plan16][2] ) = & parcel<uint64_t>();

                Coerce( sync[Plan32][0] ) = & parcel<uint8_t>();
                Coerce( sync[Plan32][1] ) = & parcel<uint16_t>();
                Coerce( sync[Plan32][2] ) = & parcel<uint64_t>();

                Coerce( sync[Plan64][0] ) = & parcel<uint8_t>();
                Coerce( sync[Plan64][1] ) = & parcel<uint16_t>();
                Coerce( sync[Plan64][2] ) = & parcel<uint32_t>();

                selectAPI();
            }

            template <typename T>
            inline Parcel<T> & parcel() const noexcept {
                return *(Parcel<T> *) &addr[ParcelProtoSize*IntegerLog2For<T>::Value];
            }


            static uint8_t * Query(const unsigned shift)
            {
                static Archon & archon = Archon::Instance();
                return static_cast<uint8_t *>( archon.query(shift) );
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


    Apex::Parcels ap(100,Apex::Plan8);


}
Y_UDONE()

