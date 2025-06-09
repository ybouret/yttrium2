
#include "y/stream/io/codec64.hpp"
#include "y/hexadecimal.hpp"

#include "y/calculus/bits-for.hpp"
#include "y/utest/run.hpp"
#include "y/system/rand.hpp"

using namespace Yttrium;

Y_UTEST(stream_io_codec64)
{

    System::Rand ran;

    for(unsigned nbit=0;nbit<=64;++nbit)
    {
        const uint64_t qw = ran.gen<uint64_t>(nbit);
        std::cerr << Hexadecimal(qw) << std::endl;
        IO::Codec64 enc(qw);
    }

    Y_PRINTV(IO::Codec64::HeaderBits);
}
Y_UDONE()
