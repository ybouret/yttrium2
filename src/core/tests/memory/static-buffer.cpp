
#include "y/memory/buffer/static.hpp"
#include "y/utest/run.hpp"
#include "y/format/hexadecimal.hpp"

using namespace Yttrium;

Y_UTEST(memory_static_buffer)
{
    Memory::StaticBuffer<3> buff;

    Hexadecimal::Display(std::cerr, (const uint8_t*)buff.ro(), buff.length() ) << std::endl;
    
}
Y_UDONE()


