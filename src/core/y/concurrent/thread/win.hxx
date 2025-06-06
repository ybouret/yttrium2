#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace Yttrium
{
	namespace Concurrent
	{

		class Thread::Code : public Thread:: Launcher
		{
		public:
			inline explicit Code(Proc userProc, void* userArgs) :
				Thread::Launcher(userProc, userArgs),
				thr(INVALID_HANDLE_VALUE),
				tid(0)
			{
				Y_Giant_Lock();
				Thread::Launcher* const self = this;
				thr = CreateThread(
					NULL,        // default security attributes
					0,           // use default stack size
					Launch,      // thread function name
					self,        // argument to thread function
					0,           // use default creation flags
					&tid);       // returns the thread identifier
				if (INVALID_HANDLE_VALUE == thr) throw Windows::Exception(::GetLastError(), "::CreateThread");
			}

			inline virtual ~Code() noexcept
			{
				if (WAIT_OBJECT_0 != ::WaitForSingleObject(thr, INFINITE))
					Windows::Error::Critical(::GetLastError(), "WaitForSingleObject");
			}



		private:
			Y_Disable_Copy_And_Assign(Code);
			HANDLE thr;
			DWORD  tid;

			static DWORD WINAPI Launch(LPVOID param) noexcept
			{
				assert(0 != param);
				static_cast<Thread::Launcher*>(param)->call();
				return 0;
			}
		};
	}
}

