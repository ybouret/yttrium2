
#include "y/calculus/bytes-for.hpp"

namespace Yttrium
{
    namespace Calculus
    {

        unsigned BytesFor:: Count(const uint8_t &b) noexcept
        {
            return (b<=0) ? unsigned(0) : unsigned(1);
        }


        unsigned BytesFor:: Count(const uint16_t &b) noexcept
        {
            static const uint16_t _1 = 1;
            static const uint16_t b8 = _1 << 8;
            if(b<=0)  return 0;
            if(b<b8) return 1;
            return 2;
        }

        unsigned BytesFor:: Count(const uint32_t &b) noexcept
        {
            static const uint32_t _1  = 1;
            static const uint32_t b8  = _1 << 8;
            static const uint32_t b16 = _1 << 16;
            static const uint32_t b24 = _1 << 24;

            if(b<=0)  return 0;
            if(b<b8)  return 1;
            if(b<b16) return 2;
            if(b<b24) return 3;
            return 4;
        }

        unsigned BytesFor:: Count(const uint64_t &b) noexcept
        {
            static const uint64_t _1  = 1;
            static const uint64_t b8  = _1 << 8;
            static const uint64_t b16 = _1 << 16;
            static const uint64_t b24 = _1 << 24;
            static const uint64_t b32 = _1 << 32;
            static const uint64_t b40 = _1 << 40;
            static const uint64_t b48 = _1 << 48;
            static const uint64_t b56 = _1 << 56;

            if(b<=0)  return 0;
            if(b<b8)  return 1;
            if(b<b16) return 2;
            if(b<b24) return 3;
            if(b<b32) return 4;
            if(b<b40) return 5;
            if(b<b48) return 6;
            if(b<b56) return 7;
            return           8;
        }

    }

}
