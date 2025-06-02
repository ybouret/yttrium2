


#include "y/memory/joint/segment.hpp"
#include "y/system/rand.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

namespace
{

}

Y_UTEST(memory_joint_segment)
{
    //Concurrent::Singulet::Verbose  = true;
    System::Rand        ran;

    Y_SIZEOF(Memory::Joint::Segment);
    Y_PRINTV(Memory::Joint::Segment::MinDataBytes);

    void *wksp[30];
    Memory::Joint::Segment::Format(wksp,sizeof(wksp));


}
Y_UDONE()

