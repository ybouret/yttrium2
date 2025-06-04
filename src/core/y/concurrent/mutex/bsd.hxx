#include "y/concurrent/nucleus.hpp"
#include <pthread.h>


namespace Yttrium
{
    namespace Concurrent
    {
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
                return 0 == pthread_mutex_trylock(data);
            }



        private:
            Y_Disable_Copy_And_Assign(Code);
        };
    }

}

