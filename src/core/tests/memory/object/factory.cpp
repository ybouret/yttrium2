
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

    static const size_t MaxBlock = 10;
    static Block        blocks[MaxBlock];
    static size_t       count = 0;


    static inline
    void fill(Memory::Object::Factory &F, System::Rand &ran)
    {
        while(count<MaxBlock)
        {
            Block & b = blocks[count];
            b.how = How( int(ran.leq(1)));
            b.len = 1 + ran.leq(100);
            switch(b.how)
            {
                case WithBlock: b.ptr = F.acquireBlock(b.len); break;
                case WithJoint: b.ptr = F.acquireJoint(b.len); break;
            }
            ++count;
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


}
Y_UDONE()

