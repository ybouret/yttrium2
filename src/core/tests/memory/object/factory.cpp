
#include "y/object/factory.hpp"
#include "y/system/rand.hpp"
#include "y/memory/stealth.hpp"
#include "y/utest/run.hpp"

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

    static inline
    void fill(Object::Factory &F, System::Rand &ran)
    {
        while(count<MaxBlock)
        {
            Block & b = blocks[count];
            b.len = ran.leq(30000); if(count<=0) b.len = 0;
            b.ptr = F.query(b.len);
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
            F.store(b.ptr,b.len);
            Y_Memory_VZero(b);
        }
    }


}

Y_UTEST(memory_object_factory)
{

    Concurrent::Singulet::Verbose = true;
    System::Rand              ran;

    Y_Memory_BZero(blocks);
    Object::Factory & F =  Object::Factory::Instance();
    std::cerr << F.callSign() << std::endl;

    fill(F,ran);
    for(size_t iter=0;iter<10;++iter)
    {
        empty(count>>1,F,ran);
        fill(F,ran);
    }
    empty(0,F,ran);
    F.display(std::cerr,0);


}
Y_UDONE()

