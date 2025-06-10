

#include "y/stream/io/chars.hpp"
#include "y/hexadecimal.hpp"

#include "y/utest/run.hpp"
#include "y/system/rand.hpp"

using namespace Yttrium;

Y_UTEST(stream_io_char)
{

    IO::Chars chars;

    chars << 'a' >> 'b' << 'c';

    std::cerr << chars << std::endl;
}
Y_UDONE()
