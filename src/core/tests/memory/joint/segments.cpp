
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

    size_t bs = 65;
    void * p = segments.acquire(bs);
    std::cerr << p << "+" << bs << std::endl;

}
Y_UDONE()
