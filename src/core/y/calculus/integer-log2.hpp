
//! \file

#ifndef Y_Calculus_IntegerLog2_Included
#define Y_Calculus_IntegerLog2_Included 1

#include "y/system/compiler.hpp"

namespace Yttrium
{

    template <size_t N> struct IntegerLog2;

    //! helper to implement IntegerLog2<2^N>
#define Y_IntegerLog2(LN2) \
template <> struct IntegerLog2<(1<<LN2)> { enum { Value = LN2 }; }


    Y_IntegerLog2(0);  //!< 2^0  = 1
    Y_IntegerLog2(1);  //!< 2^1  = 2
    Y_IntegerLog2(2);  //!< 2^2  = 4
    Y_IntegerLog2(3);  //!< 2^3  = 8
    Y_IntegerLog2(4);  //!< 2^4  = 16
    Y_IntegerLog2(5);  //!< 2^5  = 32
    Y_IntegerLog2(6);  //!< 2^6  = 64
    Y_IntegerLog2(7);  //!< 2^7  = 128
    Y_IntegerLog2(8);  //!< 2^8  = 256
    Y_IntegerLog2(9);  //!< 2^9  = 512
    Y_IntegerLog2(10); //!< 2^10 = 1024
    Y_IntegerLog2(11); //!< 2^11 = 2048
    Y_IntegerLog2(12); //!< 2^12 = 4096
    Y_IntegerLog2(13); //!< 2^13 = 8192
    Y_IntegerLog2(14); //!< 2^14 = 16384
    Y_IntegerLog2(15); //!< 2^15 = 32768

    template <typename T>
    struct IntegerLog2For
    {
        enum { Value = IntegerLog2<sizeof(T)>::Value };
    };

}

#endif
