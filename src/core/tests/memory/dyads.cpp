

#include "y/memory/dyads.hpp"
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

Y_UTEST(memory_dyads)
{
    Concurrent::Singulet::Verbose  = true;
    System::Rand        ran;

    Memory::Dyads & dyads = Memory::Dyads::Instance();

    dyads.display(std::cerr,0);

}
Y_UDONE()

