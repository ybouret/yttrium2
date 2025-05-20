
#include "y/utest/run.hpp"
#include "y/calculus/integer-log2.hpp"

using namespace Yttrium;

Y_UTEST(calculus_integer_log2)
{
    Y_PRINTV(IntegerLog2<1>::Value);
    Y_PRINTV(IntegerLog2<2>::Value);
    Y_PRINTV(IntegerLog2<4>::Value);
    Y_PRINTV(IntegerLog2<8>::Value);
    Y_PRINTV(IntegerLog2<16>::Value);
    Y_PRINTV(IntegerLog2<32>::Value);
    Y_PRINTV(IntegerLog2<64>::Value);
    Y_PRINTV(IntegerLog2<128>::Value);
    Y_PRINTV(IntegerLog2<256>::Value);
    Y_PRINTV(IntegerLog2<512>::Value);
    Y_PRINTV(IntegerLog2<1024>::Value);
    Y_PRINTV(IntegerLog2<2048>::Value);
    Y_PRINTV(IntegerLog2<4096>::Value);
    Y_PRINTV(IntegerLog2<8192>::Value);
    Y_PRINTV(IntegerLog2<16384>::Value);
    Y_PRINTV(IntegerLog2<32768>::Value);

}
Y_UDONE()
