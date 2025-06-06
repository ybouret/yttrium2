
#include "y/memory/small/blocks.hpp"
#include "y/system/rand.hpp"
#include "y/memory/stealth.hpp"
#include "y/utest/run.hpp"

#include <cstring>

using namespace Yttrium;

namespace
{


    struct Block
    {
        void * addr;
        size_t size;
    };

    static const size_t MaxBlocks = 10000;
    static Block  blk[MaxBlocks];
    static size_t num = 0;

    void fill(  Memory::Object::Blocks &blocks, System::Rand &ran )
    {
        (std::cerr << '+').flush();
        while(num<MaxBlocks)
        {
            Block &b = blk[num];
            b.size = ran.in(1000);
            b.addr = blocks.acquire(b.size);
            ++num;
        }
    }

    void empty(const size_t to, Memory::Object::Blocks &blocks, System::Rand &ran)
    {
        (std::cerr << '-').flush();
        ran.shuffle(blk,num);
        while(num>to)
        {
            --num;
            blocks.release(blk[num].addr,blk[num].size);
        }
    }

}

Y_UTEST(memory_small_blocks)
{

    Concurrent::Singulet::Verbose = true;
    System::Rand           ran;
    Memory::Object::Blocks & blocks = Memory::Object::Blocks::Instance();
    
#if 1
    Y_Memory_BZero(blk);

    std::cerr << '[';
    fill(blocks,ran);
    for(size_t iter=0;iter<10;++iter)
    {
        empty(num/2,blocks,ran);
        fill(blocks,ran);
    }
    empty(0,blocks,ran);
    std::cerr << ']' << std::endl;
#endif

    blocks.display(std::cerr,0);

    Y_SIZEOF(Memory::Object::Blocks);

}
Y_UDONE()
