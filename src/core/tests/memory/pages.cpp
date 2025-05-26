#include "y/memory/allocator/pages.hpp"
#include "y/system/rand.hpp"
#include "y/utest/run.hpp"
#include <cstring>

using namespace Yttrium;

namespace
{
    static const size_t MaxSize = 100;

    static inline void fill(void *addr[], size_t &size, Memory::Pages &pages)
    {
        assert(0!=addr);
        while(size<MaxSize)
        {
            addr[size] = pages.query();
            ++size;
        }
    }

    static inline void empty(const size_t    maxi,
                             void *          addr[],
                             size_t &        size,
                             Memory::Pages & pages,
                             System::Rand &  ran) noexcept
    {
        ran.shuffle(addr,size);
        while(size>maxi) {
            pages.store( addr[--size] );
        }
        memset(addr+size,0,(MaxSize-size)*sizeof(void*));
    }
}

Y_UTEST(memory_pages)
{
    System::Rand  ran;
    Memory::Pages pages(10);
    std::cerr << pages.bytes << " = 2^" << pages.shift << std::endl;

    pages.display(std::cerr);

    void *       addr[MaxSize];
    size_t       size = 0;
    for(size_t i=0;i<MaxSize;++i) addr[i] = 0;

    fill(addr,size,pages);
    for(size_t iter=0;iter<10;++iter)
    {

    }
    empty(0,addr,size,pages,ran);
    
    pages.display(std::cerr);

}
Y_UDONE()

