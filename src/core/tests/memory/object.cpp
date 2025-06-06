

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
            b.len     = 1+ran.leq(16384);
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
    
    template <size_t N>
    class Dummy : public Object
    {
    public:
        explicit Dummy()  : text()
        {
            Y_ASSERT(Memory::Stealth::Are0(text, N));
        }
        virtual ~Dummy() noexcept {}

        char text[N];

        static inline
        void Test()
        {
            std::cerr << "sizeof(Dummy<" << N << ">) = " << sizeof(Dummy) << std::endl;

            {
                Dummy *d = new Dummy();
                delete d;
            }

            {
                Dummy *d = new Dummy[5];
                delete []d;
            }
        }



    private:
        Y_Disable_Copy_And_Assign(Dummy);
    };


}

Y_UTEST(memory_object)
{

    Concurrent::Singulet::Verbose = true;
    System::Rand              ran;
    Y_Memory_BZero(blocks);



    fill(ran);
    for(size_t iter=0;iter<20;++iter)
    {
        empty(count>>1,ran);
        fill(ran);
    }
    empty(0,ran);

    Object::Factory::Instance().display(std::cerr, 0);

#if !defined(_MSC_VER)
    Dummy<0>::Test();
#endif
    Dummy<1>::Test();
    Dummy<2>::Test();
    Dummy<3>::Test();
    Dummy<4>::Test();
    Dummy<10>::Test();


}
Y_UDONE()

