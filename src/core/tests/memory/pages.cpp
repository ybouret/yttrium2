#include "y/memory/allocator/pages.hpp"
#include "y/utest/run.hpp"


using namespace Yttrium;

Y_UTEST(memory_pages)
{
    Memory::Pages pages(1000);
    std::cerr << pages.sizeValue << " = 2^" << pages.sizeShift << std::endl;

}
Y_UDONE()

