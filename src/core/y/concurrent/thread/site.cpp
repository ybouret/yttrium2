
#include "y/concurrent/thread/site.hpp"
#include "y/system/hardware.hpp"
#include "y/string/env.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        Site:: ~Site() noexcept
        {
            
        }

        void Site:: setup(const size_t nprocs,
                          const size_t offset,
                          const size_t stride)
        {
            assert(0==plist->size);
            assert(stride>0);
            size_t cpu = offset;
            for(size_t i=nprocs;i>0;--i,cpu += stride)
            {
                plist << cpu;
            }
        }

        void Site:: parse(const String &info)
        {
            std::cerr << "parsing '" << info << "'" << std::endl;
        }

        const char * const Site:: Y_NUM_THREADS = "Y_NUM_THREADS";

        Site:: Site() : plist()
        {
            String info;
            if( Environment::Get(info,Y_NUM_THREADS) )
            {
                parse(info);
            }
            else
                setup( Hardware::NumProcs(), 0, 1 );
        }



        Site:: Site(const String &info) :
        plist()
        {
            parse(info);
        }


        Site:: Site(const Site &site) :
        plist(site.plist)
        {
        }

        Site & Site:: operator=(const Site &site)
        {
            Site _(site);
            plist->swapListFor(*(_.plist)); // low level swap
            return *this;
        }

        Y_Ingress_Impl(Site,plist)
    }
}
