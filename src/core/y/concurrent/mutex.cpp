#include "y/concurrent/mutex.hpp"
#include "y/system/platform.hpp"
#include "y/memory/workspace.hpp"
#include "y/system/exception.hpp"
#include "y/memory/object/factory.hpp"

#if defined(Y_BSD)
#include "y/concurrent/nucleus.hpp"
#include <pthread.h>
#include <cerrno>
#endif

namespace Yttrium
{
    namespace Concurrent
    {
#if defined(Y_BSD)
        class Mutex::Code : Memory::Workspace<pthread_mutex_t>
        {
        public:
            inline Code() : Memory::Workspace<pthread_mutex_t>()
            {
                const pthread_mutexattr_t * const attr = static_cast<const pthread_mutexattr_t *>(Nucleus::Instance().get_pthread_mutex_attr());
                const int err = pthread_mutex_init(data,attr);
                if(0!=err) throw Libc::Exception(err,"pthread_mutex_init");
            }

            inline virtual ~Code() noexcept
            {
                pthread_mutex_destroy(data);
            }

            inline void lock() noexcept
            {
                const int err = pthread_mutex_lock(data);
                if(0!=err) Libc::Error::Critical(err,"pthread_mutex_lock");
            }

            inline void unlock() noexcept
            {
                const int err = pthread_mutex_unlock(data);
                if(0!=err) Libc::Error::Critical(err,"pthread_mutex_lock");
            }

            inline bool tryLock() noexcept
            {
                const int err = pthread_mutex_trylock(data);
                switch(err)
                {
                    case 0:
                        return true;
                    case EBUSY:
                        goto NO;
                    default:
                        break;
                }
                Libc::Error::Critical(err,"pthread_mutex_trylock");
            NO:
                return false;
            }



        private:
            Y_Disable_Copy_And_Assign(Code);
        };
#endif

        Mutex:: Mutex() : code( Memory::Object::Factory::Instance().createBlockAs<Code>() )
        {
        }

        Mutex:: ~Mutex() noexcept
        {
            assert(0!=code);
            Memory::Object::Factory::Location().deleteBlockAs( Coerce(code) );
        }

        void Mutex:: doLock() noexcept
        {
            assert(0!=code);
            code->lock();
        }

        void Mutex:: doUnlock() noexcept
        {
            assert(0!=code);
            code->unlock();
        }

        bool Mutex:: doTryLock() noexcept
        {
            assert(0!=code);
            return code->tryLock();
        }


    }
}
