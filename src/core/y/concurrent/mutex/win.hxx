
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace Yttrium
{
    namespace Concurrent
    {
        class Mutex :: Code : public Memory::Workspace<CRITICAL_SECTION>
        {
        public:
            inline Code() noexcept : Memory::Workspace<CRITICAL_SECTION>()
            {
                ::InitializeCriticalSection(data);
            }

            inline ~Code() noexcept
            {
                ::DeleteCriticalSection(data);
            }

            void lock() noexcept
            {
                ::EnterCriticalSection(data);
            }

            void unlock() noexcept
            {
                ::LeaveCriticalSection(data);
            }

            bool tryLock() noexcept
            {
                return ::TryEnterCriticalSection(data);
            }
        private:
            Y_Disable_Copy_And_Assign(Code);
        };
    }

}


