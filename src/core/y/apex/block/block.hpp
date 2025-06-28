//! \file

#ifndef Y_Apex_Block_Included
#define Y_Apex_Block_Included 1

#include "y/apex/block/api.hpp"
#include "y/calculus/bits-for.hpp"
#include "y/hexadecimal.hpp"

#include "y/ascii/plural.hpp"
#include <iostream>
#include <iomanip>
#include <cstring>

namespace Yttrium
{
    namespace Apex
    {

        template <typename T>
        class Block : public BlockAPI
        {
        public:
            static const ViewType View     = ViewType( IntegerLog2For<T>::Value );
            static const unsigned UnitSize = sizeof(T);
            static const unsigned UnitBits = 8 * UnitSize;


            inline explicit Block(void * const entry,
                           const size_t count) noexcept :
            BlockAPI(count,View),
            data( static_cast<T*>(entry) )
            {
                assert(0!=data);
            }

            inline virtual ~Block() noexcept
            {
            }

            size_t bits() const noexcept
            {
                if(size<=0) return 0;
                const size_t msw = size-1;
                assert(0!=data[msw]);
                return msw * UnitBits + Calculus::BitsFor::Count(data[msw]);
            }

            inline  void adjust() noexcept
            {
                while( (size>0) && (0 == data[size-1]) )
                    --size;
                assert(isValid());
            }

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

            inline virtual void resize(const size_t numBits) noexcept
            {
                size = SizeFor<T>::From(numBits);
            }

            T * const data;
        private:
            Y_Disable_Copy_And_Assign(Block);

            
            virtual void zeroPad() noexcept {
                memset(data+size,0,(maxi-size) * sizeof(T));
            }

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

