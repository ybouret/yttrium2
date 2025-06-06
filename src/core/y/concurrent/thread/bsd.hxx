
#include <pthread.h>

#include "y/memory/workspace/solitary.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        class Thread :: Code :
        public ThreadLauncher, Memory::Solitary<pthread_t>
        {
        public:
            inline explicit Code(Proc userProc, void * userArgs) :
            ThreadLauncher(userProc,userArgs)
            {
                ThreadLauncher * const self = this;
                const int err = pthread_create(data, 0, Launch, self);
                if(0!=err) throw Libc::Exception(err,"pthread_create");
            }

            inline virtual ~Code() noexcept
            {
                void *    ret = 0;
                const int err = pthread_join(*data,&ret);
                if(0!=err) Libc::Error::Critical(err, "pthread_join");
                assert(0==ret);
            }

        private:
            Y_Disable_Copy_And_Assign(Code);

            static inline
            void * Launch(void *threadLauncher) noexcept
            {
                assert(0!=threadLauncher);
                static_cast<ThreadLauncher *>(threadLauncher)->call();
                return 0;
            }

        };

    }
}
