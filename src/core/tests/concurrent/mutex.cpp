
#include "y/concurrent/mutex.hpp"
#include "y/utest/run.hpp"
#include "y/concurrent/singulet.hpp"

using namespace Yttrium;

Y_UTEST(concurrent_mutex)
{
    Concurrent::Singulet::Verbose = true;

    Concurrent::Mutex mutex;
    {
        Y_Lock(mutex);
        std::cerr << "mutex is locked" << std::endl;
        {
            Y_Lock(mutex);
            std::cerr << "mutex is locked again" << std::endl;
        }
    }


}
Y_UDONE()

