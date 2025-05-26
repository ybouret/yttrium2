
#include "y/memory/allocator/pages.hpp"
#include "y/memory/allocator/dyadic.hpp"
#include "y/check/static.hpp"
#include "y/system/exception.hpp"
#include "y/core/utils.hpp"

#include <iomanip>

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
        plist(),
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
            return (plist.size>0) ? Stealth::Zero(plist.popHead(),bytes) : allocator.acquireDyadic(shift);
        }

        void Pages:: store(void * const addr) noexcept
        {
            assert(0!=addr);
            plist.insertOderedByAddresses( Stealth::CastZeroed<Page>(addr) );
        }

        void  Pages:: display(std::ostream &os) const
        {
            os << "\t<"
            << CallSign
            << " bytes=" << std::setw(8) << bytes
            << " count=" << std::setw(8) << plist.size
            << "/>" << std::endl;
        }


    }

}

