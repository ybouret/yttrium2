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

        //______________________________________________________________________
        //
        //
        //
        //! Parcel for a given unit type
        //
        //
        //______________________________________________________________________
        template <typename T>
        class Parcel : public ParcelAPI
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definition
            //
            //__________________________________________________________________
            typedef T             Unit;                                        //!< alias
            static const size_t   BitsPerUnit = sizeof(Unit) * 8;              //!< alias
            static const PlanType Plan = PlanType( IntegerLog2For<T>::Value ); //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! build with block of memory
            /**
             \param blockAddr address of bytes
             \param blockSize available bytes
             */
            inline explicit Parcel(void * const blockAddr,
                                   const size_t blockSize) noexcept :
            ParcelAPI(blockSize/sizeof(T)),
            data( static_cast<T*>(blockAddr) )
            {
                assert( 0 == (blockSize%sizeof(T)) );
                assert( maxi>0 );

            }

            //! local parcel \param qw original/workspace
            inline explicit Parcel( uint64_t &qw ) noexcept :
            ParcelAPI( sizeof(uint64_t)/sizeof(T) ),
            data( UFormatAs<T>(qw,size) )
            {
                assert( sanity() );
            }


            //! cleanup
            inline virtual ~Parcel() noexcept {}

            //__________________________________________________________________
            //
            //
            // ReadWriteBuffer Interface
            //
            //__________________________________________________________________
            inline virtual const void * ro()     const noexcept { return data; }
            inline virtual size_t       length() const noexcept { return size * sizeof(T); }

            //__________________________________________________________________
            //
            //
            // API
            //
            //__________________________________________________________________
            inline virtual void adjust() noexcept {
                while(size>0 && 0 == data[size-1]) --size;
                assert(sanity());
            }

            inline virtual size_t bits() const noexcept {
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

            inline virtual void setOne(ParcelAPI * const sync[])  noexcept
            {
                assert(sanity());
                while(size>1) data[--size] = 0;
                data[size=1] = 1;
                assert(sanity());
                sync[0]->size = 1;
                sync[1]->size = 1;
                sync[2]->size = 1;
            }

            inline virtual void naught(ParcelAPI * const sync[])  noexcept
            {
                assert(sanity());
                while(size>0) data[--size] = 0;
                assert(sanity());
                sync[0]->size = 0;
                sync[1]->size = 0;
                sync[2]->size = 0;
            }

        private:
            //! inline SHR with carry \param curr to modify \param next next unit
            static inline void SHR(T &curr, const T next) noexcept
            {
                static const T one(1);
                static const T top = (one << (sizeof(T)*8-1));
                curr >>= 1;
                if( 0 != (next&one) ) curr |= top;
            }


        public:
            inline virtual size_t shr(ParcelAPI * const sync[]) noexcept
            {

                assert(sanity());
                switch(size)
                {
                    case 0:
                        return 0;

                    case 1:
                        if( (data[0] >>= 1) <= 0)
                        {
                            --size;
                            assert(sanity());
                            assert(0==bits());
                            return Propagate(sync,0);
                        }
                        else
                        {
                            assert( sanity() );
                            assert(bits()>0);
                            return Propagate(sync,Calculus::BitsFor::Count(data[0]));
                        }
                        
                    default: {
                        const size_t msi = size-1;
                        for(size_t i=0,j=1;i<msi;++i,++j)
                            SHR(data[i],data[j]);
                        if( (data[msi] >>= 1) <= 0)
                            --size;
                        assert(sanity());
                        break;
                    }
                }
                return Propagate(sync,bits());
            }

            
            inline virtual void resize(const size_t numBits) noexcept
            {
                size  = SizeFor<T>::From(numBits);
            }

            

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            T * const data; //!< units
        private:
            Y_Disable_Copy_And_Assign(Parcel); //!< cleanup

            //! \return checked values of units
            inline virtual bool check() const noexcept
            {
                if(size>0)
                    Y_Apex_Parcel_Check(0!=data[size-1]);
                return true;
            }

            //! print detailed informations
            /**
             \param os output stream
             \return os
             */
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


    }

}

#endif

