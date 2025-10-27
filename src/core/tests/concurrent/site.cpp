
#include "y/concurrent/thread/site.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(concurrent_site)
{
    Concurrent::Site site;
    std::cerr << site->size() << std::endl;
    std::cerr << site << std::endl;
}
Y_UDONE()


