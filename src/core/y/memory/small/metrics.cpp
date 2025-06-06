
#include "y/memory/small/metrics.hpp"
#include "y/memory/joint/segment.hpp"

namespace Yttrium
{
    namespace Memory
    {

        namespace Small
        {

            const size_t Metrics:: MediumLimitBytes = Joint::Segment::MaxSizeFor(DefaultPageShift);
        }

    }

}

