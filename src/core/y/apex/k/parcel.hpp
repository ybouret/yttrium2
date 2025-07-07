

//! \file

#ifndef Y_Apex_Parcel_Included
#define Y_Apex_Parcel_Included 1

#include "y/apex/k/parcel/api.hpp"
#include "y/apex/m/format.hpp"
#include "y/format/hexadecimal.hpp"
#include <iostream>

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

    }

}

#endif

