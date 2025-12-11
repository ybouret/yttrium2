
#include "y/ink/broker.hpp"


namespace Yttrium
{
    namespace Ink
    {
        Broker:: ~Broker() noexcept
        {
        }

        const Box &  Broker:: bbox() const noexcept { return *this; }


        Broker:: Broker(const Concurrent::Processor &proc,
                        const Area                  &area) :
        Box(area.lower,area.upper),
        Tiling(proc,bbox())
        {
        }

    }

}

