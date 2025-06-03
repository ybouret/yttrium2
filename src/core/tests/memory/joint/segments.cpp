
#include "y/memory/joint/segments.hpp"
#include "y/system/rand.hpp"
#include "y/memory/stealth.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

namespace {

    struct Block
    {
        void * addr;
        size_t size;
    };

    static const size_t MaxBlocks = 10;
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
            segments.release(b.addr);
            Y_Memory_VZero(b);
        }
    }


}

Y_UTEST(memory_joint_segments)
{
    System::Rand            ran;
    Memory::Joint::Segments segments;
    Y_SIZEOF(Memory::Joint::Segments::Slot);

    Y_Memory_BZero(blocks);

    fillWith(segments,ran);

    emptyWith(0,segments,ran);

}
Y_UDONE()
