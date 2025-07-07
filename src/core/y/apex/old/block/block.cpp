#include "y/apex/block/block.hpp"
#include "y/core/utils.hpp"
namespace Yttrium
{
    namespace Apex
    {

        uint64_t ReadLittle:: From(const uint64_t * const data, const size_t) noexcept
        {
            assert(0!=data);
            return data[0];
        }



        uint64_t ReadLittle:: From(const uint32_t * const data, const size_t size) noexcept
        {
            uint64_t res = 0;
            switch( MinOf<size_t>(size,2) )
            {
                case 2: res |= ( uint64_t(data[1]) << 32 ); // FALLTHRU
                case 1: res |= ( uint64_t(data[0]) );
            }
            return res;
        }

        uint64_t ReadLittle:: From(const uint16_t * const data, const size_t size) noexcept
        {
            uint64_t res = 0;
            switch( MinOf<size_t>(size,4) )
            {
                case 4: res |= ( uint64_t(data[3]) << 48 ); // FALLTHRU
                case 3: res |= ( uint64_t(data[2]) << 32 ); // FALLTHRU
                case 2: res |= ( uint64_t(data[1]) << 16 ); // FALLTHRU
                case 1: res |= ( uint64_t(data[0]) );
            }
            return res;

        }

        uint64_t ReadLittle:: From(const uint8_t * const data, const size_t size) noexcept
        {
            uint64_t res = 0;
            switch( MinOf<size_t>(size,8) )
            {
                case 8: res |= ( uint64_t(data[7]) << 56 ); // FALLTHRU
                case 7: res |= ( uint64_t(data[6]) << 48 ); // FALLTHRU
                case 6: res |= ( uint64_t(data[5]) << 40 ); // FALLTHRU
                case 5: res |= ( uint64_t(data[4]) << 32 ); // FALLTHRU
                case 4: res |= ( uint64_t(data[3]) << 24 ); // FALLTHRU
                case 3: res |= ( uint64_t(data[2]) << 16 ); // FALLTHRU
                case 2: res |= ( uint64_t(data[1]) <<  8 ); // FALLTHRU
                case 1: res |= ( uint64_t(data[0]) );
            }
            return res;
        }

        

    }

}


