

//! \file

#ifndef Y_Calculus_IntegerPow10_Included
#define Y_Calculus_IntegerPow10_Included 1

#include "y/system/compiler.hpp"

namespace Yttrium
{


    template <unsigned N> struct Integer10ToThe;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    template <> struct Integer10ToThe<0> { static const uint32_t Value = 1; };
    template <> struct Integer10ToThe<1> { static const uint32_t Value = 10; };
    template <> struct Integer10ToThe<2> { static const uint32_t Value = 100; };
    template <> struct Integer10ToThe<3> { static const uint32_t Value = 1000; };
    template <> struct Integer10ToThe<4> { static const uint32_t Value = 10000; };
    template <> struct Integer10ToThe<5> { static const uint32_t Value = 100000; };
    template <> struct Integer10ToThe<6> { static const uint32_t Value = 1000000; };
    template <> struct Integer10ToThe<7> { static const uint32_t Value = 10000000; };
    template <> struct Integer10ToThe<8> { static const uint32_t Value = 100000000; };
    template <> struct Integer10ToThe<9> { static const uint32_t Value = 1000000000; };
#endif // !DOXYGEN_SHOULD_SKIP_THIS

}

#endif // !Y_Calculus_IntegerPow10_Included
