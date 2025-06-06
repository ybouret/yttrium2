#include "y/concurrent/windows/semaphore.hpp"
#include "y/system/exception.hpp"

namespace Yttrium {

	namespace Windows
	{
		Semaphore:: ~Semaphore() noexcept
		{
#if defined(Y_WIN)
			assert(0 != sem_);
			::CloseHandle(sem_);
			sem_ = 0;
#endif
		}

		Semaphore::Semaphore()
#if defined(Y_WIN)
			: sem_(::CreateSemaphore(0, lMinCount, lMaxCount, 0))
		{
			if (!sem_) throw Windows::Exception(::GetLastError(), "::CreateSemaphore");
		}
#else
		{

		}
#endif


		void Semaphore::wait() noexcept
		{
#if defined(Y_WIN)
			assert(0 != sem_);
			const DWORD res = ::WaitForSingleObject(sem_, INFINITE);
			if (res != WAIT_OBJECT_0) Error::Critical(::GetLastError(), "::WaitForSingleObject( SEMAPHORE )");
#endif
		}

		void Semaphore::post() noexcept
		{
#if defined(Y_WIN)
			assert(0 != sem_);
			if (!::ReleaseSemaphore(sem_, 1, NULL)) Error::Critical(::GetLastError(), "::ReleaseSemaphore");
#endif
		}

	}
}

