#include "y/concurrent/nucleus.hpp"
#include "y/check/static.hpp"
#include "y/type/destruct.hpp"
#include "y/static/workspace/multiple.hpp"
#include "y/system/exception.hpp"
#include "y/type/ints.hpp"
#include "y/system/platform.hpp"
#include "y/core/linked/doubly.hpp"
#include "y/core/linked/list/raw.hpp"

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

        
        namespace
        {
#if defined(Y_BSD)
            class PThreadMutexAttribute : public Static::Workspace<pthread_mutexattr_t>
            {
            public:
                inline explicit PThreadMutexAttribute() : Static::Workspace<pthread_mutexattr_t>()
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
                    const int err = pthread_mutexattr_destroy(data);
                    if(0!=err) Libc::Error::Critical(err,"pthread_mutexattr_destroy");

                }

                const pthread_mutexattr_t * operator()(void) const noexcept { return data; }

            private:
                Y_Disable_Copy_And_Assign(PThreadMutexAttribute);
            };

            class PThreadMutex :
            public Static::Workspace<pthread_mutex_t>,
            public Lockable,
            public Core::DoublyLinked<PThreadMutex>
            {
            public:
                inline explicit PThreadMutex(const PThreadMutexAttribute &attr) :
                Static::Workspace<pthread_mutex_t>(),
                Lockable(),
                Core::DoublyLinked<PThreadMutex>()
                {
                    const int err = pthread_mutex_init(data, attr() );
                    if(0!=err) throw Libc::Exception(err,"pthread_mutex_init");
                }

                inline virtual ~PThreadMutex() noexcept
                {
                    const int err = pthread_mutex_destroy(data);
                    if(0!=err) Libc::Error::Critical(err,"pthread_mutex_destroy");
                }



            private:
                Y_Disable_Copy_And_Assign(PThreadMutex);
                virtual void doLock() noexcept
                {
                    const int err = pthread_mutex_lock(data);
                    if(0!=err) Libc::Error::Critical(err,"pthread_mutex_lock/%s",Nucleus::CallSign);
                }

                virtual void doUnlock() noexcept
                {
                    const int err = pthread_mutex_unlock(data);
                    if(0!=err) Libc::Error::Critical(err,"pthread_mutex_unlock/%s",Nucleus::CallSign);
                }

            };

            typedef PThreadMutex SystemMutex;
#endif

#if defined(Y_WIN)
            class WindowsMutex :
            public Static::Workspace<CRITICAL_SECTION>,
            public Lockable,
            public Core::DoublyLinked<WindowsMutex>

            {
            public:
                inline explicit WindowsMutex() noexcept :
                Static::Workspace<CRITICAL_SECTION>(),
                Lockable()
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

            typedef WindowsMutex SystemMutex;
#endif

            //! holds a few mutexes
            template <typename MUTEX, size_t N>
            class InnerLocking : public Static::Multiple<MUTEX,N>
            {
            public:
                typedef Static::Multiple<MUTEX,N> Content; //!< alias
                using Content::data;

#if defined(Y_WIN)
                //! setup with no argument
                inline explicit InnerLocking() :
                Content(),
                primary(),
                replica(),
                engaged()
                {
                    setup();
                }
#endif

#if defined(Y_BSD)
                //! setup with one argument
                template <typename T>
                inline explicit InnerLocking(T &arg) :
                Content(CopyOf,arg),
                primary(arg),
                replica(),
                engaged()
                {
                    setup();
                }
#endif

                //! cleanup
                inline virtual ~InnerLocking() noexcept { cleanup();  }

                //! query an available replica
                inline Lockable & query()
                {
                    if(replica.size<=0) throw Specific::Exception(Nucleus::CallSign,"out of inner mutex!");
                    return * engaged.pushTail( replica.popHead() );
                }


                //! primary mutex
                MUTEX            primary; //!< THE primary mutex
                RawListOf<MUTEX> replica; //!< available replica for low-level singletons
                RawListOf<MUTEX> engaged; //!< engaged replica

            private:
                Y_Disable_Copy_And_Assign(InnerLocking);
                
                inline void setup() noexcept
                {
                    for(size_t i=0;i<N;++i)
                        replica.insertOderedByAddresses( &data[i] );
                }

                inline void cleanup() noexcept {
                    replica.reset();
                    engaged.reset();
                }
            };

            typedef InnerLocking<SystemMutex,Nucleus::Replicae> InnerLockingKernel;
        }

        class Nucleus:: Code
        {
        public:
            inline Code() :
#if defined(Y_BSD)
            mutexAttributes(), kernel(mutexAttributes)
#endif
#if defined(Y_WIN)
            kernel()
#endif
            {
            }

            inline ~Code() noexcept
            {
            }

#if defined(Y_BSD)
            const PThreadMutexAttribute mutexAttributes;
#endif
            InnerLockingKernel kernel;


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
            Memory::Stealth::DestructedAndZeroed(code);
            Coerce(code) = 0;
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
            return code->kernel.primary;
        }


        Lockable & Nucleus:: queryLockable()
        {
            assert(0!=code);
            return code->kernel.query();
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

        void Nucleus:: display(std::ostream &os, size_t indent) const
        {
            assert(0!=code);
            init(os,indent) << std::endl;
			++indent;
            XML::Indent(os,indent) << "available replica mutex = " << code->kernel.replica.size << std::endl;
            XML::Indent(os,indent) << "already   engaged mutex = " << code->kernel.engaged.size << std::endl;
			--indent;
			quit(os,indent) << std::endl;
        }


#if defined(Y_BSD)
        const void * Nucleus:: get_pthread_mutex_attr() const noexcept
        {
            assert(0!=code);
            return   code->mutexAttributes();
        }
#endif

    }

    Lockable & Lockable:: Giant()
    {
        static Lockable &giant = Concurrent::Nucleus::Instance().access();
        return giant;
    }


}


