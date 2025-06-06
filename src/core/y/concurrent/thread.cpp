#include "y/concurrent/thread.hpp"
#include "y/system/platform.hpp"
#include "y/object.hpp"
#include "y/system/exception.hpp"
#include "y/ability/lockable.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        namespace
        {
            class ThreadLauncher : public Object
            {
            public:
                inline explicit ThreadLauncher(Thread::Proc userProc,
                                               void * const userArgs) noexcept :
                proc(userProc),
                args(userArgs)
                {
                }

                inline virtual ~ThreadLauncher() noexcept
                {
                    Coerce(proc)=0;
                    Coerce(args)=0;
                }

                inline void call() noexcept
                {
                    try
                    {
                        if(proc) proc(args);
                    }
                    catch(...)
                    {

                    }
                }



            private:
                Y_Disable_Copy_And_Assign(ThreadLauncher);
                Thread::Proc const proc;
                void * const       args;
            };
        }
    }

}

#if defined(Y_BSD)
#include "thread/bsd.hxx"
#endif

#if defined(Y_WIN)
#include "thread/win.hxx"
#endif

#include "y/type/destroy.hpp"


namespace Yttrium
{
    namespace Concurrent
    {
        Thread:: Thread(Proc proc, void * const args) :
        code( new Code(proc,args) )
        {
        }

        Thread:: ~Thread() noexcept
        {
            assert(0!=code);
            Destroy(code);
        }

    }

}
