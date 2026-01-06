#include "y/stream/io/bits.hpp"
#include "y/utest/run.hpp"

//#include "y/concurrent/singulet.hpp"

using namespace Yttrium;

Y_UTEST(stream_io_bits)
{
    //Concurrent::Singulet::Verbose  = true;
    IO::Bits bits;

    bits << true;
    bits << false;
    std::cerr << bits << std::endl;

}
Y_UDONE()


