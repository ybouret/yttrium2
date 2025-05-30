
#include "y/memory/object/book/pages.hpp"
#include "y/memory/allocator/dyadic.hpp"
#include "y/check/static.hpp"
#include "y/system/exception.hpp"
#include "y/core/utils.hpp"
#include "y/xml/attribute.hpp"

#include <iomanip>

namespace Yttrium
{
    namespace Memory
    {
        namespace Object
        {
            const char * const Pages:: CallSign = "Memory::Object::Pages";

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


            void Pages:: release_() noexcept
            {
                Y_Lock(memIO.access);
                while(plist.size>0)
                    memIO.releaseUnlockedDyadic(plist.popTail(),shift);
            }

            Pages:: ~Pages() noexcept
            {
                release_();
            }


            size_t Pages:: count() const noexcept { return plist.size; }

            void Pages:: release() noexcept
            {
                release_();
            }



            void * Pages:: query()
            {
                return (plist.size>0) ? Page::Addr(plist.popHead(),bytes) : memIO.acquireDyadic(shift);
            }




            void Pages:: store(void * const addr) noexcept
            {
                assert(0!=addr);
                plist.insertOderedByAddresses( Page::Cast(addr) );
                assert(plist.isOrderedBy( plist.CompareAddresses, Sign::StriclyIncreasing ) );
            }

            void Pages:: cache(size_t numPages)
            {
                Y_Lock(memIO.access);
                while(numPages-- > 0) store( memIO.acquireUnlockedDyadic(shift) );
            }




            void  Pages:: display(std::ostream &os, const size_t indent) const
            {
                initProlog(os,indent);
                os << XML::Attribute("bytes",bytes,8);
                os << XML::Attribute("count",plist.size,8);
                initEpilog(os,true) << std::endl;
            }


        }
    }

}

