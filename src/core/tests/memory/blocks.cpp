
#include "y/memory/object/blocks.hpp"
#include "y/system/rand.hpp"
#include "y/utest/run.hpp"

#include <cstring>

using namespace Yttrium;

namespace
{


}

Y_UTEST(memory_blocks)
{
    Memory::Object::Blocks blocks(1000);

    void * p = blocks.acquire(10); std::cerr << "p@" << p << std::endl;
    blocks.release(p,10);

}
Y_UDONE()
