//! \file

#ifndef Y_Apex_Block_Included
#define Y_Apex_Block_Included 1

#include "y/apex/block/api.hpp"
#include "y/apex/m/size-for.hpp"
#include "y/hexadecimal.hpp"

#include "y/ascii/plural.hpp"
#include <iostream>
#include <iomanip>
#include <cstring>

namespace Yttrium
{
    namespace Apex
    {

        struct ReadLittle
        {
            static uint64_t From(const uint64_t *, const size_t) noexcept;
            static uint64_t From(const uint32_t *, const size_t) noexcept;
            static uint64_t From(const uint16_t *, const size_t) noexcept;
            static uint64_t From(const uint8_t  *, const size_t) noexcept;
        };

        //______________________________________________________________________
        //
        //
        //
        //! Concrete Block
        //
        //
        //______________________________________________________________________
        template <typename T>
        class Block : public BlockAPI
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            static const ViewType View     = ViewType( IntegerLog2For<T>::Value ); //!< alias
            static const unsigned UnitSize = sizeof(T);                            //!< bytes per T
            static const unsigned UnitBits = 8 * UnitSize;                         //!< bits per T

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup with pre-allocated memory
            /**
             \param entry available memory
             \param count number of words
             */
            inline explicit Block(void * const entry,
                                  const size_t count) noexcept :
            BlockAPI(count,View),
            data( static_cast<T*>(entry) )
            {
                assert(0!=data);
            }

            //! cleanup
            inline virtual ~Block() noexcept
            {
            }

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            inline virtual size_t update(BlockAPI * const sync[]) noexcept
            {
                assert(0!=sync);
                adjust();
                const size_t numBits = bits();
                assert(0!=sync[0]); sync[0]->resize(numBits);
                assert(0!=sync[1]); sync[1]->resize(numBits);
                assert(0!=sync[2]); sync[2]->resize(numBits);
                return numBits;
            }

            inline virtual void   naught(BlockAPI * const sync[])  noexcept
            {
                assert( isValid() );
                while(size>0)
                    data[--size] = 0;
                assert( isValid() );
                assert(0!=sync[0]); sync[0]->size=0;
                assert(0!=sync[1]); sync[1]->size=0;
                assert(0!=sync[2]); sync[2]->size=0;
            }

            inline virtual void   build1(BlockAPI * const sync[])  noexcept
            {
                assert( isValid() );
                while(size>1)
                    data[--size] = 0;
                data[0] = 1;
                size    = 1;
                assert( isValid() );
                assert(0!=sync[0]); sync[0]->size=1;
                assert(0!=sync[1]); sync[1]->size=1;
                assert(0!=sync[2]); sync[2]->size=1;
            }


            inline virtual void resize(const size_t numBits) noexcept
            {
                size = SizeFor<T>::From(numBits);
            }

            inline virtual uint64_t little() const noexcept
            {
                return ReadLittle::From(data,size);
            }

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! compute bits from current state \return computed bits
            size_t bits() const noexcept
            {
                assert(isValid());
                if(size<=0) return 0;
                const size_t msw = size-1;
                assert(0!=data[msw]);
                return msw * UnitBits + Calculus::BitsFor::Count(data[msw]);
            }

            //! adjust assuming msb could be zero
            inline  void adjust() noexcept
            {
                while( (size>0) && (0 == data[size-1]) )
                    --size;
                assert(isValid());
            }


            //__________________________________________________________________
            //
            //
            // members
            //
            //__________________________________________________________________
            T * const data; //!< big-endian data
        private:
            Y_Disable_Copy_And_Assign(Block); //!< discarding


            inline virtual bool doCheck() const noexcept
            {
                assert(size<=maxi);
                if(size>0) Y_Block_Check(0!=data[size-1]);
                for(size_t i=size;i<maxi;++i) Y_Block_Check(0==data[i]);
                return true;
            }

            inline virtual std::ostream & print(std::ostream &os) const
            {
                os << "@." << std::setw(2) << UnitBits << '[';
                size_t i=size;
                while(i-- > 0)
                    os << ' ' << Hexadecimal(data[i]);
                os << ' ' << ']' << ":unit" << ASCII::Plural::s(size) << "=" << size;
                return os;
            }
        };
    }

}

#endif

