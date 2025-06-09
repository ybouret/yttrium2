
#include "y/stream/io/codec64.hpp"
#include "y/calculus/bits-for.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(stream_io_codec64)
{
    Y_PRINTV(IO::Codec64::MaxInputBits);
    Y_PRINTV(IO::Codec64::MaxInputBytes);

    const unsigned MaxInputBits = IO::Codec64::MaxInputBits;
    Y_PRINTV(BitsFor(MaxInputBits));

    const unsigned MaxInputBytes = IO::Codec64::MaxInputBytes;
    Y_PRINTV(BitsFor(MaxInputBytes));


}
Y_UDONE()
