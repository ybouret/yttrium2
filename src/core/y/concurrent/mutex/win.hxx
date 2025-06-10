
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace Yttrium
{
	namespace Concurrent
	{
		class Mutex::Code : public Static::Solitary<CRITICAL_SECTION>
		{
		public:
			inline Code() noexcept : Static::Solitary<CRITICAL_SECTION>()
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


#if 0
//==================================================================
			//
			//
			//! Legacy condition on windows
			//
			//
			//==================================================================
class Condition
{
public:
	inline Condition() :
		cv_attr(),
		cv_lock(cv_attr),
		cv_waiting(0),
		cv_signals(0),
		cv_wait_sem(),
		cv_done_sem()
	{
	}

	inline ~Condition() noexcept
	{
	}

	inline void wait(Mutex& m) noexcept
	{
		/* Obtain the protection mutex, and increment the number of waiters.
		 This allows the signal mechanism to only perform a signal if there
		 are waiting threads.
		 */
		cv_lock.lock();
		++cv_waiting;
		cv_lock.unlock();

		/* Unlock the mutex, as is required by condition variable semantics */
		m.unlock();
		//mutex_api::unlock(m);


		/* Wait for a signal */
		cv_wait_sem.wait();


		/* Let the signaler know we have completed the wait, otherwise
		 the signaler can race ahead and get the condition semaphore
		 if we are stopped between the mutex unlock and semaphore wait,
		 giving a deadlock.  See the following URL for details:
		 http://www-classic.be.com/aboutbe/benewsletter/volume_III/Issue40.html
		 */

		cv_lock.lock();
		if (cv_signals > 0)
		{
			/* We always notify the signal thread that we are done */
			cv_done_sem.post();
			--cv_signals;
		}
		--cv_waiting;
		cv_lock.unlock();

		/* Lock the mutex, as is required by condition variable semantics */
		m.lock();
		//mutex_api::lock(m);
	}

	void signal() noexcept
	{
		cv_lock.lock();
		if (cv_waiting > cv_signals)
		{
			++cv_signals;
			cv_wait_sem.post();
			cv_lock.unlock();
			cv_done_sem.wait();
		}
		else
			cv_lock.unlock();
	}

	void broadcast() noexcept
	{
		/* If there are waiting threads not already signalled, then
		 signal the condition and wait for the thread to respond.
		 */
		cv_lock.lock();
		if (cv_waiting > cv_signals)
		{
			const int num_waiting = cv_waiting - cv_signals;
			cv_signals = cv_waiting;
			for (int i = 0; i < num_waiting; ++i)
			{
				cv_wait_sem.post();
			}
			/* Now all released threads are blocked here, waiting for us.
			 Collect them all.
			 */
			cv_lock.unlock();
			for (int i = 0; i < num_waiting; ++i)
			{
				cv_done_sem.wait();
			}
		}
		else
		{
			cv_lock.unlock();
		}
	}


private:
	Y_DISABLE_COPY_AND_ASSIGN(Condition);
	MutexAttribute   cv_attr;      /*!< dummy mutex initializer      */
	Mutex            cv_lock;      /*!< condition lock               */
	int              cv_waiting;   /*!< waiting count                */
	int              cv_signals;   /*!< signals count                */
	Win32::Semaphore cv_wait_sem;  /*!< Win32 semaphore when waiting */
	Win32::Semaphore cv_done_sem;  /*!< Win32 semaphore when done    */

};
#endif

#include "y/concurrent/windows/semaphore.hpp"

namespace Yttrium
{
	namespace Concurrent
	{
		class Condition::Code
		{
		public:
			inline explicit Code() :
				cv_lock(),
				cv_waiting(0),
				cv_signals(0),
				cv_wait_sem(),
				cv_done_sem()
			{

			}

			inline virtual ~Code() noexcept
			{
			}

			inline void wait(Mutex& m) noexcept
			{
				/*	Obtain the protection mutex, and increment the number of waiters.
					This allows the signal mechanism to only perform a signal if there
					are waiting threads.
				*/
				cv_lock.lock();
				++cv_waiting;
				cv_lock.unlock();

				/* Unlock the mutex, as is required by condition variable semantics */
				m.unlock();

				/* Wait for a signal */
				cv_wait_sem.wait();


				/* Let the signaler know we have completed the wait, otherwise
				 the signaler can race ahead and get the condition semaphore
				 if we are stopped between the mutex unlock and semaphore wait,
				 giving a deadlock.  See the following URL for details:
				 http://www-classic.be.com/aboutbe/benewsletter/volume_III/Issue40.html
				 */

				cv_lock.lock();
				if (cv_signals > 0)
				{
					/* We always notify the signal thread that we are done */
					cv_done_sem.post();
					--cv_signals;
				}
				--cv_waiting;
				cv_lock.unlock();

				/* Lock the mutex, as is required by condition variable semantics */
				m.lock();
			}

			inline void signal() noexcept
			{
				cv_lock.lock();
				if (cv_waiting > cv_signals)
				{
					++cv_signals;
					cv_wait_sem.post();
					cv_lock.unlock();
					cv_done_sem.wait();
				}
				else
					cv_lock.unlock();
			}

			inline void broadcast() noexcept
			{
				/*	If there are waiting threads not already signalled, then
					signal the condition and wait for the thread to respond.
				*/
				cv_lock.lock();
				if (cv_waiting > cv_signals)
				{
					const int num_waiting = cv_waiting - cv_signals;
					cv_signals = cv_waiting;
					for (int i = 0; i < num_waiting; ++i)
					{
						cv_wait_sem.post();
					}
					/* Now all released threads are blocked here, waiting for us.
					 Collect them all.
					 */
					cv_lock.unlock();
					for (int i = 0; i < num_waiting; ++i)
					{
						cv_done_sem.wait();
					}
				}
				else
				{
					cv_lock.unlock();
				}
			}
		private:
			Y_Disable_Copy_And_Assign(Code);
			Mutex::Code        cv_lock;      /*!< condition lock               */
			int                cv_waiting;   /*!< waiting count                */
			int                cv_signals;   /*!< signals count                */
			Windows::Semaphore cv_wait_sem;  /*!< Win32 semaphore when waiting */
			Windows::Semaphore cv_done_sem;  /*!< Win32 semaphore when done    */
		};
	}
}
