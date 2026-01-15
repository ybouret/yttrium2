
#include "y/ink/broker.hpp"


namespace Yttrium
{
    namespace Ink
    {
        Broker:: ~Broker() noexcept
        {
        }

        
        Broker:: Broker(const Concurrent::Processor &proc,
                        const Area                  &area) :
        Tiling(proc,BoxType(area.lower,area.upper))
        {
        }

        Broker:: Broker(const Concurrent::Processor &proc) :
        Tiling(proc)
        { }

        void Broker:: prep(const Area &area)
        {
            const BoxType box(area.lower,area.upper);
            if( remap(box) )
            {
                
            }
        }


    }

}

