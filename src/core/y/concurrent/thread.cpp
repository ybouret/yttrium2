#include "y/concurrent/thread.hpp"
#include "y/system/platform.hpp"
#include "y/object.hpp"
#include "y/system/exception.hpp"
#include "y/ability/lockable.hpp"
#include <iostream>

namespace Yttrium
{
	namespace Concurrent
    {


        class Thread::Launcher : public Object
        {
        public:
            inline explicit Launcher(Thread::Proc userProc,
                                     void* const userArgs) noexcept :
            proc(userProc),
            args(userArgs)
            {
            }

            inline virtual ~Launcher() noexcept
            {
                Coerce(proc) = 0;
                Coerce(args) = 0;
            }

            inline void call() noexcept
            {
                try
                {
                    if (proc) proc(args);
                }
                catch (...)
                {

                }
            }



        private:
            Y_Disable_Copy_And_Assign(Launcher);
            Thread::Proc const proc;
            void* const       args;
        };

        static inline
        void DisplayThreadWarning(const Exception &excp) noexcept
        {
            if(true)
            {
                Y_Giant_Lock();
                std::cerr << "*** " << excp.when() << " : " << excp.what() << std::endl;
            }
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
		Thread::Thread(Proc proc, void* const args) :
			code(new Code(proc, args))
		{
		}

		Thread:: ~Thread() noexcept
		{
			assert(0 != code);
			Destroy(code);
		}

	}

}

#if defined Y_THREAD_AFFINITY
#error "Y_THREAD_AFFINITY shouldn't be defined"
#endif

namespace Yttrium
{
    namespace Concurrent
    {
#if defined(Y_Darwin)
#define Y_THREAD_AFFINITY 1
#include <mach/thread_policy.h>
#include <mach/thread_act.h>

        bool Thread::assign(const size_t j) noexcept
        {
            assert(code);
            thread_affinity_policy_data_t policy_data = { int(j) };
            mach_port_t                   mach_thread = pthread_mach_thread_np(code->get());
            const int                     mach_result = thread_policy_set(mach_thread, THREAD_AFFINITY_POLICY, (thread_policy_t)&policy_data, THREAD_AFFINITY_POLICY_COUNT);
            if (KERN_SUCCESS != mach_result)
            {
                const Mach::Exception excp(mach_result, "thread_policy_set");
                DisplayThreadWarning(excp);
                return false;
            }
            else
            {
                return true;
            }

        }

#endif

#if defined(Y_Linux)|| defined(Y_FreeBSD)
#   define Y_THREAD_AFFINITY 1
#   if defined(Y_FreeBSD)
#      include <pthread_np.h>
#      define Y_CPU_SET cpuset_t
#   else
#      define Y_CPU_SET cpu_set_t
#   endif

        bool   Thread::assign(const size_t j) noexcept
        {
            Y_CPU_SET the_cpu_set;
            CPU_ZERO(&the_cpu_set);
            CPU_SET(j, &the_cpu_set);
            const int err = pthread_setaffinity_np(code->get(), sizeof(Y_CPU_SET), &the_cpu_set);
            if (err != 0)
            {
                const Libc::Exception excp(err, "pthread_setaffinity_np");
                DisplayThreadWarning(excp);
                return false;
            }
            else
            {
                return true;
            }
        }

#endif


#if defined(Y_WIN)
#   define Y_THREAD_AFFINITY 1
        bool Thread::assign(const size_t j) noexcept
        {
            const DWORD_PTR mask = DWORD_PTR(1) << j;
            if (!::SetThreadAffinityMask(code->get(), mask))
            {
                const DWORD err = ::GetLastError();
                const Windows::Exception excp(err, "::SetThreadAffinityMask");
                DisplayThreadWarning(excp);
                return false;
            }
            else
            {
                return true;
            }
        }
#endif

#if defined(Y_SunOS)
#   define Y_THREAD_AFFINITY 1
#include <sys/types.h>
#include <sys/processor.h>
#include <sys/procset.h>

        bool Thread::assign(const size_t j) noexcept
        {
            const int res = processor_bind(P_LWPID, idtype_t(code->get()), j, NULL);
            if (0 != res)
            {
                const Exception excp("processor_bind failure");
                DisplayThreadWarning(excp);
                return false;
            }
            else
            {
                return true;
            }
        }

#endif


#if ! defined(Y_THREAD_AFFINITY)
#warning "No Thread Affinity"
        bool Thread::assign(const size_t) noexcept
        {
            const Exception excp("No Thread Affinity");
            DisplayThreadWarning(excp);
            return false;
        }
#endif



    }

}


