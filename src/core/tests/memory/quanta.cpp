

#include "y/memory/allocator/quanta.hpp"
#include "y/system/rand.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

namespace
{
    struct Block
    {
        void  *addr;
        size_t size;
    };
}

Y_UTEST(memory_quanta)
{
    Concurrent::Singulet::Verbose  = true;
    System::Rand        ran;
    Memory::Quanta &    allocator = Memory::Quanta::Instance();

    allocator.display(std::cerr,0);


#if 0
    Block        blocks[1000];
    const size_t numBlocks = sizeof(blocks)/sizeof(blocks[0]);
    for(size_t i=0;i<numBlocks;++i)
    {
        Block &block = blocks[i];
        block.size   = ran.leq(1000);
        std::cerr << block.size << "->";
        block.addr   = allocator.acquire(block.size);
        std::cerr << block.size << std::endl;
    }
    allocator.display(std::cerr,0);

    ran.shuffle(blocks,numBlocks);
    for(size_t i=0;i<numBlocks;++i)
    {
        allocator.release(blocks[i].addr, blocks[i].size);
    }
    allocator.display(std::cerr,0);
#endif

}
Y_UDONE()

