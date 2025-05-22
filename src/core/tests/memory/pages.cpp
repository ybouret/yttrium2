#include "y/memory/allocator/dyadic.hpp"
#include "y/utest/run.hpp"


#include "y/calculus/base2.hpp"
#include "y/system/exception.hpp"
#include "y/core/utils.hpp"
#include "y/core/linked/list.hpp"
#include "y/memory/stealth.hpp"
#include "y/check/static.hpp"

namespace Yttrium
{

    namespace Memory
    {
        struct Page
        {
            typedef Core::ListOf<Page> List;
            Page *next;
            Page *prev;
        };

        class Pages : public Page::List
        {
        public:
            static const char * const CallSign;



            Pages(const size_t requestedPageSize) :
            Page::List(),
            sizeShift(0),
            sizeValue( ComputePageSize(requestedPageSize, Coerce(sizeShift)) ),
            allocator( Dyadic::Instance() )
            {
                Y_STATIC_CHECK(Dyadic::MinBlockBytes>=sizeof(Page),BadDyadicMetrics);
            }

            ~Pages() noexcept {}


            void *query()
            {
                return (size>0) ? Stealth::Zero(popHead(),sizeValue) : allocator.acquireDyadic(sizeShift);
            }

            void store(void * const addr) noexcept
            {
                assert(0!=addr);
                pushHead( Stealth::CastZeroed<Page>(addr) );
            }



            const unsigned sizeShift;
            const size_t   sizeValue;
            Dyadic &       allocator;

        private:
            Y_Disable_Copy_And_Assign(Pages);

            static size_t ComputePageSize(const size_t requestedPageSize, unsigned &computedBlockShift)
            {
                if(requestedPageSize> Dyadic::MaxBlockBytes ) throw Specific::Exception(CallSign,"requestedPageSize overflow");
                return NextPowerOfTwo( MaxOf(requestedPageSize,Dyadic::MinBlockBytes), computedBlockShift);
            }

        };

        const char * const Pages:: CallSign = "Memory::Pages";
    }
}

using namespace Yttrium;

Y_UTEST(memory_pages)
{
    Memory::Pages pages(1000);
    std::cerr << pages.sizeValue << " = 2^" << pages.sizeShift << std::endl;

}
Y_UDONE()

