
#include "y/system/rand.hpp"
#include "y/memory/stealth.hpp"
#include "y/check/usual.hpp"
#include <ctime>
#include <cstdlib>
#include <cmath>

namespace Yttrium
{
    namespace System
    {
        Rand:: Rand() noexcept
        {
            srand( unsigned(time(0)) );
        }

        Rand:: ~Rand() noexcept
        {

        }

        template <>
        float Rand:: to<float>() noexcept
        {
            static const float denom = static_cast<float>(RAND_MAX)+1.0f;
            return ( static_cast<float>( rand() ) + 0.5f ) / denom;
        }

        template <>
        double Rand:: to<double>() noexcept
        {
            static const double denom = static_cast<double>(RAND_MAX)+1.0;
            return ( static_cast<double>( rand() ) + 0.5 ) / denom;
        }

        template <>
        long double Rand:: to<long double>() noexcept
        {
            static const long double denom = static_cast<long double>(RAND_MAX)+1.0L;
            return ( static_cast<long double>( rand() ) + 0.5L ) / denom;
        }

        bool Rand:: choice() noexcept
        {
            return to<double>() <= 0.5;
        }


        template <typename T> static inline
        T randFill(Rand &ran) noexcept
        {
            T result=0;
            for(size_t i=sizeof(T)*8;i>0;--i)
            {
                result <<= 1;
                if( ran.choice() ) result |= 1;
            }
            return result;
        }

        template <>
        uint8_t Rand:: to<uint8_t>() noexcept
        {
            return randFill<uint8_t>(*this);
        }

        template <>
        uint16_t Rand:: to<uint16_t>() noexcept
        {
            return randFill<uint16_t>(*this);
        }

        template <>
        uint32_t Rand:: to<uint32_t>() noexcept
        {
            return randFill<uint32_t>(*this);
        }

        template <>
        uint64_t Rand:: to<uint64_t>() noexcept
        {
            return randFill<uint64_t>(*this);
        }



        size_t Rand:: leq(const size_t n) noexcept
        {
            return static_cast<size_t>( floor( double(n) * to<double>() + 0.5 ) );
        }

        void Rand:: shuffle(void * const blockAddr,
                            const size_t numBlocks,
                            const size_t blockSize) noexcept
        {
            assert( Good(blockAddr,numBlocks) );
            assert( blockSize > 0 );
            if(numBlocks<=1) return;

            uint8_t * const base = static_cast<uint8_t *>(blockAddr);
            for(size_t i=numBlocks-1;i>0;--i)
            {
                const size_t j = leq(i);
                Memory::Stealth::Swap(base+i*blockSize, base+j*blockSize,blockSize);
            }
        }


        void Rand:: fill(void * const blockAddr, const size_t blockSize) noexcept
        {
            assert( Good(blockAddr,blockSize) );
            uint8_t * base = static_cast<uint8_t *>(blockAddr);
            for(size_t i=blockSize;i>0;--i)
            {
                *(base++) = static_cast<uint8_t>( 1 + floor( to<double>() * 255.0 + 0.5) );
            }
        }



    }

}
