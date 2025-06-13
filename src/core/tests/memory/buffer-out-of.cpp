

#include "y/memory/buffer/out-of.hpp"
#include "y/utest/run.hpp"
#include "y/hexadecimal.hpp"
#include "y/memory/allocator/pooled.hpp"

using namespace Yttrium;

Y_UTEST(memory_buffer_out_of)
{

    Memory::BufferOutOf<Memory::Pooled> buff(3);
    
    Hexadecimal::Display(std::cerr, (const uint8_t*)buff.ro(), buff.length() ) << std::endl;

}
Y_UDONE()


