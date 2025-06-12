


#include "y/stream/io/chars.hpp"
#include "y/memory/io/supply-of.hpp"
#include "y/hexadecimal.hpp"

#include "y/utest/run.hpp"
#include "y/system/rand.hpp"


namespace Yttrium
{
    
}



using namespace Yttrium;

Y_UTEST(stream_io_char)
{
    Memory::SupplyOf<IO::Char> &ioc = Memory::SupplyOf<IO::Char>::Instance();
    
#if 0
    IO::Chars chars;

    chars << 'a' >> 'b' << 'c';

    std::cerr << chars << std::endl;
#endif
    
}
Y_UDONE()
