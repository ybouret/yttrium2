
#include "y/memory/object/arena.hpp"
#include "y/memory/stealth.hpp"
#include "y/system/rand.hpp"
#include "y/utest/run.hpp"
#include "y/check/usual.hpp"

#include <cstring>

using namespace Yttrium;

namespace
{

}

Y_UTEST(memory_arena)
{
    Y_SIZEOF(Memory::Arena);

    Memory::Arena arena(100,0);
    

}
Y_UDONE()
