
#include "y/memory/allocator/pages.hpp"
#include "y/memory/allocator/dyadic.hpp"
#include "y/check/static.hpp"
#include "y/system/exception.hpp"
#include "y/core/utils.hpp"

namespace Yttrium
{
    namespace Memory
    {
        const char * const Pages:: CallSign = "Memory::Pages";


        Pages:: Pages(const size_t requestedPageSize) :
        Page::List(),
        sizeShift(0),
        sizeValue( ComputePageSize(requestedPageSize, Coerce(sizeShift)) ),
        allocator( Dyadic::Instance() )
        {
            Y_STATIC_CHECK(Dyadic::MinBlockBytes>=sizeof(Page),BadDyadicMetrics);
        }

        Pages:: ~Pages() noexcept
        {
        }

        void * Pages:: query()
        {
            return (size>0) ? Stealth::Zero(popHead(),sizeValue) : allocator.acquireDyadic(sizeShift);
        }

        void Pages:: store(void * const addr) noexcept
        {
            assert(0!=addr);
            pushHead( Stealth::CastZeroed<Page>(addr) );
        }

        size_t Pages:: ComputePageSize(const size_t requestedPageSize,
                                       unsigned &   computedBlockShift)
        {
            if(requestedPageSize> Dyadic::MaxBlockBytes ) throw Specific::Exception(CallSign,"requestedPageSize overflow");
            return NextPowerOfTwo( MaxOf(requestedPageSize,Dyadic::MinBlockBytes), computedBlockShift);
        }

    }

}

