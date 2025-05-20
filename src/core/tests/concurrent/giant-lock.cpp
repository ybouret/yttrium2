
#include "y/lockable.hpp"
#include "y/concurrent/singulet.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(concurrent_giant_lock)
{
    Concurrent::Singulet::Verbose = true;

    {
        Y_Giant_Lock();
    }

}
Y_UDONE()

