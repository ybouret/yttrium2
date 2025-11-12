#include "y/concurrent/api/kernel.hpp"
#include "y/concurrent/fake-lock.hpp"
#include "y/concurrent/thread.hpp"
#include "y/concurrent/mutex.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        void KernelTest:: ST(Kernel &k)
        {
            FakeLock fl;
            Context  cx(fl,1,0);
            k(cx);
        }

        namespace
        {
            class MTExec
            {
            public:
                inline MTExec(Kernel &k, const size_t sz, const size_t rk) :
                kernel(k),
                mutex(),
                context(mutex,sz,rk),
                thread( Launch, this )
                {

                }

                inline ~MTExec() noexcept
                {
                }

                inline void run() noexcept
                {
                    try
                    {
                        kernel(context);
                    }
                    catch(...)
                    {

                    }

                }

                Kernel &kernel;
                Mutex   mutex;
                Context context;
                Thread  thread;

            private:
                Y_Disable_Copy_And_Assign(MTExec);
                static inline void Launch(void * const args) noexcept
                {
                    assert(args);
                    static_cast<MTExec *>(args)->run();
                }
            };
        }

        void KernelTest:: MT(Kernel &k, const size_t sz, const size_t rk)
        {
            volatile MTExec mt(k,sz,rk);
        }
    }
}

