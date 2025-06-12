
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
    Concurrent::Singulet::Verbose = true;
    
#if 1
    IO::Chars chars;
    chars << 'a';
    //chars << 'a' >> 'b' << 'c';
    std::cerr << chars << std::endl;
#endif
    
}
Y_UDONE()
