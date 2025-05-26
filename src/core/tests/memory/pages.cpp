#include "y/memory/allocator/pages.hpp"
#include "y/utest/run.hpp"


using namespace Yttrium;

Y_UTEST(memory_pages)
{
    Memory::Pages pages(10);
    std::cerr << pages.bytes << " = 2^" << pages.shift << std::endl;

}
Y_UDONE()

