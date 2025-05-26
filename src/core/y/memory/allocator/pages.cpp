
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


        static unsigned checkPageSizeShift(const unsigned userShift)
        {
            if(userShift< Dyadic::MinBlockShift||userShift>Dyadic::MaxBlockShift)
                throw Specific::Exception(Pages::CallSign,"page shift not in [%u:%u]", Dyadic::MinBlockShift,Dyadic::MaxBlockShift);
            return userShift;
        }

        Pages:: Pages(const unsigned userShift) :
        Page::List(),
        shift( checkPageSizeShift(userShift) ),
        bytes( size_t(1) << shift ),
        allocator( Dyadic::Instance() )
        {
            Y_STATIC_CHECK(Dyadic::MinBlockBytes>=sizeof(Page),BadDyadicMetrics);
        }

        Pages:: ~Pages() noexcept
        {
        }

        void * Pages:: query()
        {
            return (size>0) ? Stealth::Zero(popHead(),bytes) : allocator.acquireDyadic(shift);
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

