


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

    static inline
    void fillSeg(Memory::Joint::Segment * const segment, System::Rand &ran)
    {
        while(count<MaxBlocks)
        {
            Block &b = blocks[count];
            b.size   = ran.leq(100);
            b.addr   = segment->acquire(b.size);
            if(!b.addr)
            {
                b.size=0;
                break;
            }

            ++count;
            const uint32_t crc = segment->crc32();
            ran.fill(b.addr,b.size);
            Y_ASSERT(segment->crc32() == crc);
        }
        segment->display(std::cerr);
        
    }

    static inline
    void emptySeg(const size_t to, Memory::Joint::Segment * const segment, System::Rand &ran)
    {
        ran.shuffle(blocks,count);
        while(count>to)
        {
            Block &b = blocks[--count];
            Memory::Joint::Segment * const s = Memory::Joint::Segment::Release(b.addr);
            Y_ASSERT(s==segment);
            if(s->isEmpty())
            {
                Y_ASSERT(0==count);
            }
        }
       segment->display(std::cerr);
    }

}

Y_UTEST(memory_joint_segment)
{
    System::Rand        ran;

    Y_SIZEOF(Memory::Joint::Segment);
    Y_PRINTV(Memory::Joint::Segment::MinDataBytes);

    Y_Memory_BZero(blocks);

    void *wksp[128];
    Memory::Joint::Segment *segment = Memory::Joint::Segment::Format(wksp,Base2<size_t>::ExactLog(sizeof(wksp)));
    Y_CHECK( segment->isEmpty() );




    segment->display(std::cerr);

    fillSeg(segment,ran);
    for(int iter=0;iter<10;++iter)
    {
        emptySeg(count>>1,segment,ran);
        fillSeg(segment,ran);
    }
    emptySeg(0,segment,ran);
    Y_CHECK( segment->isEmpty() );
    Y_CHECK( segment->param.bytes == sizeof(wksp) );


    {
        Y_PRINTV( Memory::Joint::Segment::MaxRequest );
        Y_PRINTV( Memory::Joint::Segment::ShiftFor(0) );
        Y_PRINTV( Memory::Joint::Segment::ShiftFor(1000) );
        Y_PRINTV( Memory::Joint::Segment::MinDataShift );
        Y_PRINTV( Memory::Joint::Segment::MaxDataShift );

    }

}
Y_UDONE()

