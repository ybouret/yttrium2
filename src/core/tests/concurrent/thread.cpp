


#include "y/concurrent/thread.hpp"
#include "y/ability/lockable.hpp"
#include "y/utest/run.hpp"




using namespace Yttrium;

namespace
{

    static void Run(void * const args) noexcept
    {
        Y_Giant_Lock();
        (std::cerr << "Now Running with a=" << (*(int *)args) << std::endl).flush();
    }
}


Y_UTEST(concurrent_thread)
{
    int a=7;
    Concurrent::Thread t1(Run,&a);
    Y_Thread_Message("Bye");
}
Y_UDONE()

