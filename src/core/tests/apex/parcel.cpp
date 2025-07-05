#include "y/apex/m/archon.hpp"
#include "y/apex/m/format.hpp"

#include "y/utest/run.hpp"
#include "y/random/park-miller.hpp"
#include "y/format/hexadecimal.hpp"

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
                        os << '[' << Hexadecimal(data[--i]) << ']';
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
    }

}

namespace
{
    template <typename T>
    static inline void testParcel(const Apex::Parcel<T> &p, const size_t numBits)
    {
        std::cerr << p << std::endl;
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

}
Y_UDONE()

