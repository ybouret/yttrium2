

#include "y/memory/allocator/quanta.hpp"
#include "y/system/rand.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

namespace
{
    struct Block
    {
        void  *addr;
        size_t size;
    };
}

Y_UTEST(memory_quanta)
{
    Concurrent::Singulet::Verbose  = true;
    System::Rand        ran;

    Memory::Quanta & quanta = Memory::Quanta::Instance();

    quanta.display(std::cerr,0);

}
Y_UDONE()

