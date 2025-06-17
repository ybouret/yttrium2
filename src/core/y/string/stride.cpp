#include "y/string/stride.hpp"
#include "y/core/utils.hpp"
#include "y/memory/allocator/pooled.hpp"

namespace Yttrium
{

    namespace Core
    {

        StrideMetrics:: ~StrideMetrics() noexcept
        {
            
        }

        StrideMetrics:: StrideMetrics(const size_t minimalCapacity,
                                      const size_t bytesPerChar) noexcept :
        size(0),
        capacity( MaxOf<size_t>(minimalCapacity,7) ),
        address(0),
        numChars( capacity+1 ),
        obtained( numChars * bytesPerChar )
        {
            assert(bytesPerChar>0);
            static Memory::Pooled &mgr = Memory::Pooled::Instance();
            Coerce(address) = mgr.acquire( Coerce(obtained) ); assert( obtained >= numChars * bytesPerChar );
            Coerce(numChars) = obtained / bytesPerChar;
            Coerce(capacity) = numChars - 1;
        }
    }

}


