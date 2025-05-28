
#include "y/hashing/des64.hpp"
#include <cstdio>

namespace Yttrium
{
    namespace Hashing
    {

        const char * const DES64:: CallSign = "Hashing::DES64";

        DES64::  DES64() noexcept {}
        DES64:: ~DES64() noexcept {}

        const char * DES64:: callSign() const noexcept { return CallSign; }

#define Y_DES64(i) \
{\
const uint32_t it = rword;             \
const uint32_t ia = (it) ^ X##i;       \
const uint32_t il = ia & 0xffff;       \
const uint32_t ih = ia >>  0x10;       \
const uint32_t ib = (il*il) + ~(ih*ih);\
rword = lword ^ (( ( (ib >> 0x10) | ((ib & 0xffff) << 0x10)) ^ Y##i)+ (il*ih) );\
lword = it;\
}

        void DES64:: operator()(uint32_t &lword, uint32_t &rword) const noexcept
        {
            static const uint32_t X0 = 0xbaa96887L;
            static const uint32_t X1 = 0x1e17d32cL;
            static const uint32_t X2 = 0x03bcdc3cL;
            static const uint32_t X3 = 0x0f33d1b2L;

            static const uint32_t Y0 = 0x4b0f3b58L;
            static const uint32_t Y1 = 0xe874f0c3L;
            static const uint32_t Y2 = 0x6955c5a6L;
            static const uint32_t Y3 = 0x55a7ca46L;

            Y_DES64(0) Y_DES64(1) Y_DES64(2) Y_DES64(3)
        }

        bool DES64:: test() const noexcept
        {
            static const uint32_t input[4][2] =
            {
                {1,  1},
                {1, 99},
                {99, 1},
                {99,99}
            };

            static const uint32_t output[4][2] =
            {
                {0x604D1DCE, 0x509C0C23},
                {0xD97F8571, 0xA66CB41A},
                {0x7822309D, 0x64300984},
                {0xD7F376F0, 0x59BA89EB}
            };

            printf("Testing %s\n", callSign());
            for(size_t i=0;i<4;++i)
            {
                uint32_t lo = input[i][0];
                uint32_t hi = input[i][1];
                (*this)(lo,hi);
                printf("  %08X | %08X\n",lo,output[i][0]);
                printf("  %08X | %08X\n",hi,output[i][1]);
                if(output[i][0]!=lo || output[i][1]!=hi)
                    return false;
            }

            return true;
        }

    }

}
