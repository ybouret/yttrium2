
#include "y/concurrent/thread/site.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

namespace
{
    static inline void Show(const Concurrent::Site site)
    {
        std::cerr << "site = " << site << std::endl;
    }
}

Y_UTEST(concurrent_site)
{
    Concurrent::Site site(Concurrent::Site::Default);
    std::cerr << site->size() << std::endl;

    Show(site);
    Show(3);
    Show(Concurrent::Site::Default);
    
}
Y_UDONE()


