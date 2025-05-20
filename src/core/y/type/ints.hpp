
//! \file

#ifndef Y_Type_Ints_Included
#define Y_Type_Ints_Included 1

#include "y/system/types.hpp"

namespace Yttrium
{
    template <typename T> struct UnsignedInt;

    template <>
    struct UnsignedInt<uint8_t>
    {
        typedef uint8_t      Type;
        static const uint8_t Minimum = 0x00;
        static const uint8_t Maximum = 0xff;
    };

    template <>
    struct UnsignedInt<uint16_t>
    {
        typedef uint16_t      Type;
        static const uint16_t Minimum = 0x0000;
        static const uint16_t Maximum = 0xffff;
    };


    template <>
    struct UnsignedInt<uint32_t>
    {
        typedef uint32_t      Type;
        static const uint32_t Minimum = 0x00000000;
        static const uint32_t Maximum = 0xffffffff;
    };


    template <>
    struct UnsignedInt<uint64_t>
    {
        typedef uint64_t      Type;
        static const uint64_t Minimum = 0x0000000000000000ULL;
        static const uint64_t Maximum = 0xffffffffffffffffULL;
    };


}

#endif

