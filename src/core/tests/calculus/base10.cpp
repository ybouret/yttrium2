
#include "y/utest/run.hpp"
#include "y/calculus/base10.hpp"
#include "y/random/park-miller.hpp"

#include <cmath>
using namespace Yttrium;




Y_UTEST(calculus_base10)
{
    typedef Base10<uint64_t> B10;

    Y_PRINTV(B10::DigitsFor(0));
    Y_PRINTV(B10::DigitsFor(1));
    Y_PRINTV(B10::DigitsFor(9));
    Y_PRINTV(B10::DigitsFor(10));
    Y_PRINTV(B10::DigitsFor(20));
    Y_PRINTV(B10::DigitsFor(99));
    Y_PRINTV(B10::DigitsFor(100));
    Y_PRINTV(B10::DigitsFor(101));


}
Y_UDONE()
