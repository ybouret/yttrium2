#include "y/concurrent/nucleus.hpp"
#include <pthread.h>


namespace Yttrium
{
    namespace Concurrent
    {
        class Mutex::Code : public Memory::Solitary<pthread_mutex_t>
        {
        public:
            inline Code() : Memory::Solitary<pthread_mutex_t>()
            {
                const pthread_mutexattr_t * const attr = static_cast<const pthread_mutexattr_t *>(Nucleus::Instance().get_pthread_mutex_attr());
                const int err = pthread_mutex_init(data,attr);
                if(0!=err) throw Libc::Exception(err,"pthread_mutex_init");
            }

            inline virtual ~Code() noexcept
            {
                const int err = pthread_mutex_destroy(data);
                if(0!=err) Libc::Error::Critical(err,"pthread_mutex_destroy");

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


namespace Yttrium
{
    namespace Concurrent
    {

        class Condition :: Code : Memory::Workspace<pthread_cond_t>
        {
        public:
            explicit Code() : Memory::Workspace<pthread_cond_t>()
            {
                const int err = pthread_cond_init(data,0);
                if(0!=err) throw Libc::Exception(err,"pthread_cond_init");
            }

            virtual ~Code() noexcept
            {
                const int err = pthread_cond_destroy(data);
                if(0!=err) Libc::Error::Critical(err,"pthread_cond_destroy");
            }

            inline void wait(Mutex &mutex) noexcept
            {
                assert(0!=mutex.code);
                const int err = pthread_cond_wait(data,& **mutex.code);
                if(0!=err) Libc::Error::Critical(err,"pthread_cond_wait");
            }

            inline void signal() noexcept
            {
                const int err = pthread_cond_signal(data);
                if(0!=err) Libc::Error::Critical(err,"pthread_cond_signal");
            }

            inline void broadcast() noexcept
            {
                const int err = pthread_cond_broadcast(data);
                if(0!=err) Libc::Error::Critical(err,"pthread_cond_broadcast");
            }


        private:
            Y_Disable_Copy_And_Assign(Code);
            
        };
    }

}

