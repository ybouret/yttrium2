
#include "y/memory/joint/segments.hpp"
#include "y/system/rand.hpp"
#include "y/memory/stealth.hpp"
#include "y/utest/run.hpp"
#include "y/memory/small/ledger.hpp"

using namespace Yttrium;

namespace {

    struct Block
    {
        void * addr;
        size_t size;
    };

    static const size_t MaxBlocks = 500;
    static Block        blocks[MaxBlocks];
    static size_t       count = 0;

    static inline
    void fillWith(Memory::Joint::Segments & segments,
                  System::Rand            & ran)
    {
        while(count<MaxBlocks)
        {
            Block &b = blocks[count];
            assert(0==b.addr);
            b.size = ran.leq(10000);
            b.addr = segments.acquire(b.size);
            ++count;
            const uint32_t crc = segments.crc32();
            ran.fill(b.addr,b.size);
            Y_ASSERT(segments.crc32()==crc);
        }
    }

    static inline
    void emptyWith(const size_t              target,
                   Memory::Joint::Segments & segments,
                   System::Rand            & ran) noexcept
    {
        ran.shuffle(blocks,count);
        while(count>target)
        {
            Block &b = blocks[--count];
            segments.release(b.addr,b.size);
            Y_Memory_VZero(b);
        }
    }


}

Y_UTEST(memory_joint_segments)
{
    System::Rand            ran;
    Y_SIZEOF(Memory::Joint::Segments::Slot);

    Y_Memory_BZero(blocks);

    {
        Memory::Joint::Segments segments;
        fillWith(segments,ran);
        for(size_t iter=0;iter<10;++iter)
        {
            emptyWith(count>>1,segments,ran);
            fillWith(segments,ran);
        }

        emptyWith(0,segments,ran);

        Memory::Small::Ledger::Instance().display(std::cerr,0);
    }

    Memory::Small::Ledger::Instance().display(std::cerr,0);

}
Y_UDONE()
