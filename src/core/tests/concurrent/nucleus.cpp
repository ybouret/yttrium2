#include "y/concurrent/nucleus.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

Y_UTEST(concurrent_nucleus)
{
    Concurrent::Singulet::Verbose = true;
    Concurrent::Nucleus &nucleus = Concurrent::Nucleus::Instance();
    std::cerr << "end of " << program << " for " << nucleus.callSign() << std::endl;

    {
        Y_Lock(nucleus.access());
        {
            Y_Lock(nucleus.access());
        }
    }

    {
        Lockable &replica = nucleus.queryLockable();
        Y_Lock(replica);
    }

    nucleus.display(std::cerr,0);

}
Y_UDONE()

