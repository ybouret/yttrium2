
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

    size_t blockSize = 100;
    size_t pageBytes = 0;

    if(argc>1) blockSize = atol(argv[1]);
    if(argc>2) pageBytes = atol(argv[2]);

    Memory::Arena arena(blockSize,pageBytes);

    while( arena.acquire() )
        ;


}
Y_UDONE()
