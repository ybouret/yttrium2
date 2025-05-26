#include "y/memory/allocator/pages.hpp"
#include "y/system/rand.hpp"
#include "y/utest/run.hpp"
#include <cstring>

using namespace Yttrium;

Y_UTEST(memory_pages)
{
    Memory::Pages pages(10);
    std::cerr << pages.bytes << " = 2^" << pages.shift << std::endl;
    pages.display(std::cerr);

    const size_t MaxSize = 100;
    void *       addr[MaxSize];
    size_t       size = 0;
    memset(addr,0,sizeof(addr));

    addr[0] = pages.query();

    pages.store( addr[0] );



}
Y_UDONE()

