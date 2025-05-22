#include "y/concurrent/nucleus.hpp"
#include "y/check/static.hpp"
#include "y/type/destruct.hpp"
#include "y/memory/workspace.hpp"
#include "y/system/exception.hpp"
#include "y/type/ints.hpp"
#include "y/system/platform.hpp"

#if defined(Y_BSD)
#include <pthread.h>
#endif

#if defined(Y_WIN)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include <iostream>

namespace Yttrium
{

    namespace Concurrent
    {

#if defined(Y_BSD)
        class PThreadMutexAttribute : public Memory::Workspace<pthread_mutexattr_t>
        {
        public:
            inline explicit PThreadMutexAttribute() : Memory::Workspace<pthread_mutexattr_t>()
            {
                {
                    const int err = pthread_mutexattr_init(data);
                    if(0!=err) throw Libc::Exception(err,"pthread_mutexattr_init");
                }

                {
                    const int err = pthread_mutexattr_settype(data,PTHREAD_MUTEX_RECURSIVE);
                    if(0!=err)
                    {
                        pthread_mutexattr_destroy(data);
                        throw Libc::Exception(err,"pthread_mutexattr_settype");
                    }
                }
            }

            inline virtual ~PThreadMutexAttribute() noexcept
            {
                pthread_mutexattr_destroy(data);
            }

            const pthread_mutexattr_t * operator()(void) const noexcept { return data; }

        private:
            Y_Disable_Copy_And_Assign(PThreadMutexAttribute);
        };

        class PThreadMutex :
        public Memory::Workspace<pthread_mutex_t>,
        public Lockable
        {
        public:
            inline explicit PThreadMutex(const PThreadMutexAttribute &attr) :
            Memory::Workspace<pthread_mutex_t>()
            {
                const int err = pthread_mutex_init(data, attr() );
                if(0!=err) throw Libc::Exception(err,"pthread_mutex_init");
            }

            inline virtual ~PThreadMutex() noexcept
            {
                pthread_mutex_destroy(data);
            }

        private:
            Y_Disable_Copy_And_Assign(PThreadMutex);
            virtual void doLock() noexcept
            {
                const int err = pthread_mutex_lock(data);
                if(0!=err) Libc::Error::Critical(err,"pthread_mutex_lock");
            }

            virtual void doUnlock() noexcept
            {
                const int err = pthread_mutex_unlock(data);
                if(0!=err) Libc::Error::Critical(err,"pthread_mutex_lock");
            }

        };

#endif

#if defined(Y_WIN)
		class WindowsMutex : public Memory::Workspace<CRITICAL_SECTION>, public Lockable
		{
		public:
			inline explicit WindowsMutex() : Memory::Workspace<CRITICAL_SECTION>()
			{
				::InitializeCriticalSection(data);
			}

			inline virtual ~WindowsMutex() noexcept
			{
				::DeleteCriticalSection(data);
			}
		private:
			Y_Disable_Copy_And_Assign(WindowsMutex);
			inline virtual void doLock() noexcept
			{
				::EnterCriticalSection(data);
			}

			inline virtual void doUnlock() noexcept
			{
				::LeaveCriticalSection(data);
			}

		};
#endif

        class Nucleus:: Code
        {
        public:
            inline Code() :
#if defined(Y_BSD)
            mutexAttributes(), mutex(mutexAttributes)
#endif
#if defined(Y_WIN)
			mutex()
#endif
            {
            }

            inline ~Code() noexcept
            {
            }

#if defined(Y_BSD)
            const PThreadMutexAttribute mutexAttributes;
            PThreadMutex                mutex;
#endif

#if defined(Y_WIN)
			WindowsMutex mutex;
#endif



        private:
            Y_Disable_Copy_And_Assign(Code);
        };

        static void    * codeWorkspace[    Alignment::WordsFor<Nucleus::Code>::Count ];
        static void    * nucleusWorkspace[ Alignment::WordsFor<Nucleus>::Count       ];
        static Nucleus * nucleus = 0;


        void Nucleus:: SelfDestruct(void *) noexcept
        {
            assert(0!=nucleus);
            nucleus->~Nucleus();
            nucleus = 0;
            Y_Memory_BZero(nucleusWorkspace);
        }

        Nucleus:: Nucleus() : Singulet(), code(0)
        {
            if(Verbose) Display("+",CallSign,LifeTime);

            try {
                code = new ( Y_Memory_BZero(codeWorkspace) ) Code();
            }
            catch(...)
            {
                throw;
            }

        }

        Nucleus:: ~Nucleus() noexcept
        {
            if(Verbose) Display("~",CallSign,LifeTime);
            assert(0!=code);
            Nullify(code);
            Y_Memory_BZero(codeWorkspace);
        }

        const char * const Nucleus:: CallSign = "Concurrent::Nucleus";

        const char * Nucleus:: callSign() const noexcept
        {
            return CallSign;
        }

        Singulet::Longevity Nucleus:: lifeTime() const noexcept
        {
            return LifeTime;
        }

        Lockable & Nucleus:: access() noexcept
        {
            assert(0!=code);
            return code->mutex;
        }


        Nucleus & Nucleus:: Instance()
        {
            Y_STATIC_CHECK(sizeof(nucleusWorkspace)>=sizeof(Nucleus),BadNucleusWorkspace);
            Y_STATIC_CHECK(sizeof(codeWorkspace)>=sizeof(Nucleus::Code),BadNucleusCodeWorkspace);

            if(0==nucleus) {

                // create resources
                try
                {
                    nucleus =  new ( Y_Memory_BZero(nucleusWorkspace) ) Nucleus();
                }
                catch(...)
                {
                    Y_Memory_BZero(nucleusWorkspace);
                    nucleus = 0;
                    throw;
                }

                // register
                {
                    void * const args = 0;
                    try
                    {
                        System::AtExit::Perform(SelfDestruct,args,LifeTime);
                    }
                    catch(...)
                    {
                        SelfDestruct(args);
                        throw;
                    }
                }
            }
            return *nucleus;
        }

    }

        Lockable & Lockable:: Giant()
        {
            static Lockable &giant = Concurrent::Nucleus::Instance().access();
            return giant;
        }


}


