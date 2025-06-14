
#include "y/stream/io/chars.hpp"
#include "y/utest/run.hpp"
#include "y/system/rand.hpp"
#include "y/concurrent/singulet.hpp"


namespace Yttrium
{
    
}



using namespace Yttrium;

Y_UTEST(stream_io_char)
{
    //Concurrent::Singulet::Verbose = true;
    IO::Chars chars;
    chars << 'a' >> 'b' << 'c';
    std::cerr << chars << std::endl;
    IO::Chars ccopy = chars;
    std::cerr << ccopy << std::endl;
    ccopy.release();
    std::cerr << ccopy << std::endl;
    ccopy = chars;
    std::cerr << ccopy << std::endl;
}
Y_UDONE()
