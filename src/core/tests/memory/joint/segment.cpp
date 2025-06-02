


#include "y/memory/joint/segment.hpp"
#include "y/system/rand.hpp"
#include "y/memory/stealth.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

namespace
{
    struct Block
    {
        void  *addr;
        size_t size;
    };

    static const size_t MaxBlocks = 100;
    static Block  blocks[MaxBlocks];
    static size_t count = 0;

    void fill(Memory::Joint::Segment * const segment, System::Rand &ran)
    {
        while(count<MaxBlocks)
        {
            Block &b = blocks[count];
            b.size   = ran.leq(100);
            b.addr   = Memory::Joint::Segment::Acquire(segment,b.size);
            if(!b.addr)
            {
                b.size=0;
                break;
            }
        }
    }

    }

Y_UTEST(memory_joint_segment)
{
    System::Rand        ran;

    Y_SIZEOF(Memory::Joint::Segment);
    Y_PRINTV(Memory::Joint::Segment::MinDataBytes);

    Y_Memory_BZero(blocks);

    void *wksp[100];
    Memory::Joint::Segment *segment = Memory::Joint::Segment::Format(wksp,sizeof(wksp));

    Memory::Joint::Segment::Display(segment,std::cerr);

    fill(segment,ran);

    Memory::Joint::Segment::Display(segment,std::cerr);


}
Y_UDONE()

