#include "y/string/stride.hpp"
#include "y/core/utils.hpp"
#include "y/memory/allocator/pooled.hpp"

namespace Yttrium
{

    namespace Core
    {



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

        StrideMetrics:: ~StrideMetrics() noexcept
        {
            assert(numChars-1==capacity);
            assert(capacity>0);
            assert(size<=capacity);
            assert(obtained>=numChars);
            assert( Memory::Pooled::Exists() );

            static Memory::Pooled & mgr = Memory::Pooled::Location();
            mgr.release( Coerce(address), Coerce(obtained) );
            Coerce(numChars) = 0;
            Coerce(capacity) = 0;
            Coerce(size)     = 0;
        }
    }

}


