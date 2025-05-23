
#include "y/utest/run.hpp"
#include "y/calculus/gcd.hpp"
#include "y/system/rand.hpp"

using namespace Yttrium;

namespace
{
    template <typename T>
    static inline void testGCD(T a, T b)
    {
        const T g = GreatestCommonDivisor(a,b);
        std::cerr << "gcd(" << uint64_t(a) << "," << uint64_t(b) << ") = " << uint64_t(g) << std::endl;
    }
}

Y_UTEST(calculus_gcd)
{

    testGCD<uint8_t>(9,27);
    testGCD<uint16_t>(9,81);
    testGCD<uint32_t>(13*4,13*7);
    testGCD<uint64_t>(13*7,13*11);


}
Y_UDONE()
