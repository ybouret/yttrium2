
#include "y/memory/joint/segments.hpp"
#include "y/system/rand.hpp"
#include "y/memory/stealth.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;


Y_UTEST(memory_joint_segments)
{
    System::Rand ran;
    Memory::Joint::Segments segments;
    Y_SIZEOF(Memory::Joint::Segments::Slot);
}
Y_UDONE()
