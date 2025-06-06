
#include "y/object/factory.hpp"
#include "y/system/rand.hpp"
#include "y/memory/stealth.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

namespace
{
    enum How
    {
        WithSingle = 0,
        WithPooled = 1
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

#if 1
    static inline
    void fill(Object::Factory &F, System::Rand &ran)
    {
        while(count<MaxBlock)
        {
            Block & b = blocks[count];
            b.how = How( int(ran.leq(1)));
            b.len = 1 + ran.leq(100); Y_ASSERT(b.len>0);
            switch(b.how)
            {
                case WithSingle: b.ptr = F.acquireSingle(b.len); break;
                case WithPooled: b.ptr = F.acquirePooled(b.len); break;
            }
            ++count;
        }
    }


    static inline
    void empty(const size_t              to,
               Object::Factory         & F,
               System::Rand &            ran) noexcept
    {
        ran.shuffle(blocks,count);
        while(count>to)
        {
            Block & b = blocks[--count];
            switch(b.how)
            {
                case WithSingle: F.releaseSingle(b.ptr,b.len); break;
                case WithPooled: F.releasePooled(b.ptr,b.len); break;
            }
            Y_Memory_VZero(b);
        }
    }
#endif


}

Y_UTEST(memory_object_factory)
{

    Concurrent::Singulet::Verbose = true;
    System::Rand              ran;

    Y_Memory_BZero(blocks);
#if 1
    Object::Factory & F =  Object::Factory::Instance();
    std::cerr << F.callSign() << std::endl;

    fill(F,ran);
    for(size_t iter=0;iter<10;++iter)
    {
        empty(count>>1,F,ran);
        fill(F,ran);
    }
    empty(0,F,ran);
#endif
    F.display(std::cerr,0);


}
Y_UDONE()

