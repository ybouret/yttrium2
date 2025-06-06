

#include "y/object/factory.hpp"
#include "y/system/rand.hpp"
#include "y/memory/stealth.hpp"
#include "y/memory/object/metrics.hpp"
#include "y/utest/run.hpp"
#include "y/concurrent/singulet.hpp"

using namespace Yttrium;

namespace
{

    struct Block
    {
        void * ptr;
        size_t len;
    };

    static const size_t MaxBlock = 1000;
    static Block        blocks[MaxBlock];
    static size_t       count = 0;

#if 1

    static inline
    void fill(System::Rand &ran)
    {
        while(count<MaxBlock)
        {
            Block & b = blocks[count];
            b.len     = 1+ran.leq(Memory::Object::Metrics::MediumLimitBytes-1);
            b.ptr     = Object:: operator new(b.len);
            ++count;
        }
    }


    static inline
    void empty(const size_t              to,
               System::Rand &            ran) noexcept
    {
        ran.shuffle(blocks,count);
        while(count>to)
        {
            Block & b = blocks[--count];
            Object:: operator delete(b.ptr,b.len);
            Y_Memory_VZero(b);
        }
    }

#endif
    

}

Y_UTEST(memory_object)
{

    Concurrent::Singulet::Verbose = true;
    System::Rand              ran;
    Y_Memory_BZero(blocks);



    fill(ran);
    for(size_t iter=0;iter<10;++iter)
    {
        empty(count>>1,ran);
        fill(ran);
    }
    empty(0,ran);

    Object::Factory::Instance().display(std::cerr, 0);
    

}
Y_UDONE()

