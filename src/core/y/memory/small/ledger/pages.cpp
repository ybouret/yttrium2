
#include "y/memory/small/ledger/pages.hpp"
#include "y/memory/allocator/dyadic.hpp"
#include "y/check/static.hpp"
#include "y/exception.hpp"
#include "y/core/utils.hpp"
#include "y/xml/attribute.hpp"

#include <iomanip>

namespace Yttrium
{
    namespace Memory
    {
        namespace Small
        {
            const char * const Pages:: CallSign = "Memory::Small::Pages";

            const char * Pages:: callSign() const noexcept
            {
                return CallSign;
            }

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
            memIO( Dyadic::Instance() )
            {
                Y_STATIC_CHECK(Dyadic::MinBlockBytes>=sizeof(Page),BadDyadicMetrics);
            }


            void Pages:: releaseTo(const size_t newSize) noexcept
            {
                assert(newSize<=plist.size);
                Y_Lock(memIO.access);
                while(plist.size>newSize)
                    memIO.releaseUnlockedDyadic(plist.popTail(),shift);
            }

            Pages:: ~Pages() noexcept
            {
                releaseTo(0);
            }


            size_t Pages:: count() const noexcept { return plist.size; }

            void Pages:: release() noexcept
            {
                releaseTo(0);
            }

            void Pages:: gc(const uint8_t amount) noexcept
            {
                releaseTo( NewSize(amount,plist.size) );
            }



            void * Pages:: query()
            {
                return (plist.size>0) ? Page::Addr(plist.popHead(),bytes) : memIO.acquireDyadic(shift);
            }




            void Pages:: store(void * const addr) noexcept
            {
                assert(0!=addr);
                plist.insertOderedByAddresses( Page::Cast(addr) );
                assert(plist.isOrderedByNodeAddress());
            }

            void Pages:: cache(size_t numPages)
            {
                Y_Lock(memIO.access);
                while(numPages-- > 0) store( memIO.acquireUnlockedDyadic(shift) );
            }




            void  Pages:: display(std::ostream &os,size_t indent) const
            {
                initProlog(os,indent);
                os << XML::Attribute("bytes",bytes,8);
                os << XML::Attribute("count",plist.size,8);
                initEpilog(os,true);
            }


        }
    }

}

