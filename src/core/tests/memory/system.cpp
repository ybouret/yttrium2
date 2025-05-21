#include "y/memory/system.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

namespace
{

}

Y_UTEST(memory_system)
{
    Concurrent::Singulet::Verbose  = true;

    Memory::System &allocator = Memory::System::Instance();

    size_t blockSize = 10;
    void * blockAddr = allocator.acquire(blockSize);
    std::cerr << "Allocated " << blockSize << " @" << blockAddr << std::endl;

}
Y_UDONE()

