
#include "y/memory/object/factory.hpp"
#include "y/system/rand.hpp"
#include "y/memory/stealth.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

namespace
{
    enum How
    {
        WithBlock = 0,
        WithJoint = 1
    };

    struct Block
    {
        How    how;
        void * ptr;
        size_t len;
    };

    static const size_t MaxBlock = 1000;
    static Block        blocks[MaxBlock];
    static size_t       count = 0;


    static inline
    void fill(Memory::Object::Factory &F, System::Rand &ran)
    {
        while(count<MaxBlock)
        {
            Block & b = blocks[count];
            b.how = How( int(ran.leq(1)));
            b.len = 1 + ran.leq(100); Y_ASSERT(b.len>0);
            switch(b.how)
            {
                case WithBlock: b.ptr = F.acquireBlock(b.len); break;
                case WithJoint: b.ptr = F.acquireJoint(b.len); break;
            }
            ++count;
        }
    }


    static inline
    void empty(const size_t              to,
               Memory::Object::Factory & F,
               System::Rand &            ran) noexcept
    {
        ran.shuffle(blocks,count);
        while(count>to)
        {
            Block & b = blocks[--count];
            switch(b.how)
            {
                case WithBlock: F.releaseBlock(b.ptr,b.len); break;
                case WithJoint: F.releaseJoint(b.ptr,b.len); break;
            }
            Y_Memory_VZero(b);
        }
    }


}

Y_UTEST(memory_object_factory)
{

    Concurrent::Singulet::Verbose = true;
    System::Rand              ran;
    Memory::Object::Factory & F = Memory::Object::Factory::Instance();
    std::cerr << F.callSign() << std::endl;

    Y_Memory_BZero(blocks);

    fill(F,ran);
    for(size_t iter=0;iter<10;++iter)
    {
        empty(count>>1,F,ran);
        fill(F,ran);
    }
    empty(0,F,ran);

}
Y_UDONE()

