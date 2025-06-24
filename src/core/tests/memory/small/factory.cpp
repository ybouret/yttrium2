
#include "y/object/factory.hpp"
#include "y/system/rand.hpp"
#include "y/memory/stealth.hpp"
#include "y/utest/run.hpp"
#include "y/memory/small/metrics.hpp"

using namespace Yttrium;

namespace
{

    struct Block
    {
        void * ptr;
        size_t len;
    };

    static const size_t MaxBlock = 2000;
    static Block        blocks[MaxBlock];
    static size_t       count = 0;

    static inline
    void fill(Object::Factory &F, System::Rand &ran)
    {
        while(count<MaxBlock)
        {
            Block & b = blocks[count];
            b.len = ran.leq(100000); if(count<=0) b.len = 0;
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

    //Concurrent::Singulet::Verbose = true;

    Object::Factory & F =  Object::Factory::Instance();

    std::cerr << "Random query/store" << std::endl;
    {
        System::Rand              ran;

        Y_Memory_BZero(blocks);
        std::cerr << F.callSign() << std::endl;

        fill(F,ran);
        for(size_t iter=0;iter<10;++iter)
        {
            empty(count>>1,F,ran);
            fill(F,ran);
        }
        empty(0,F,ran);
        F.display(std::cerr,0);
        std::cerr << std::endl;
    }

    Y_PRINTV(Memory::Small::Metrics::LimitObjectBytes);
    Y_PRINTV(Memory::Small::Metrics::MediumLimitBytes);

    std::cerr << std::endl;

    std::cerr << "Systematic query/store" << std::endl;
    for(size_t blockSize=1;blockSize<=1000;++blockSize)
    {
        void * addr = F.query(blockSize);
        F.store(addr,blockSize);
    }
    std::cerr << std::endl;


    std::cerr << "Systematic acquire/release" << std::endl;
    for(size_t blockSize=1;blockSize<=1000;++blockSize)
    {
        size_t bs   = blockSize;
        void * addr = F.acquire(bs);
        F.release(addr,bs);
    }
    std::cerr << std::endl;



}
Y_UDONE()

