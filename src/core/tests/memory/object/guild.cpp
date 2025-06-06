
#include "y/concurrent/singulet.hpp"
#include "y/memory/object/guild.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(memory_object_guild)
{

    Concurrent::Singulet::Verbose  = 1;
    Memory::Object::Guild guild(18);

    Y_PRINTV(guild.blockSize());

}
Y_UDONE()

