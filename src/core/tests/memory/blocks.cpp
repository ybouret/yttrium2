
#include "y/memory/object/blocks.hpp"
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

    static const size_t MaxBlocks = 1000;
    static Block  blk[MaxBlocks];
    static size_t num = 0;

    void fill(  Memory::Object::Blocks &blocks, System::Rand &ran )
    {
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
        ran.shuffle(blk,num);
        while(num>0)
        {
            --num;
            blocks.release(blk[num].addr,blk[num].size);
        }
    }


}

Y_UTEST(memory_blocks)
{
    System::Rand           ran;
    Memory::Object::Blocks blocks(1000);

    void * p = blocks.acquire(10); std::cerr << "p@" << p << std::endl;
    blocks.release(p,10);

    Y_Memory_BZero(blk);

    fill( blocks, ran );
    empty(0,blocks,ran);

}
Y_UDONE()
