//! \file

#ifndef Y_Concurrent_Thread_Launcher_Included
#define Y_Concurrent_Thread_Launcher_Included 1

#include "y/concurrent/thread.hpp"
#include "y/calculus/alignment.hpp"
#include "y/memory/stealth.hpp"
#include "y/concurrent/runnable.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        class ThreadData : public Runnable
        {
        public:
            typedef void (ThreadData::*Meth)(void);


            template <typename OBJECT,typename METHOD> inline
            explicit ThreadData(OBJECT &o, METHOD m) noexcept :
            mine( & ThreadData::call<OBJECT,METHOD> ),
            host( &o ),
            wksp()
            {
                Memory::Stealth::Copy(wksp,&m,sizeof(METHOD));
            }

            virtual ~ThreadData() noexcept {}

            virtual void run() noexcept {
                (*this.*mine)();
            }

        private:
            Y_Disable_Copy_And_Assign(ThreadData);
            Meth   const mine;
            void * const host;
            void *       wksp[Alignment::WordsFor<Meth>::Count];

            template <typename OBJECT, typename METHOD>
            void call() noexcept
            {
                OBJECT & o = *Memory::Stealth::Cast<OBJECT>(host);
                METHOD & m = *Memory::Stealth::Cast<METHOD>(wksp);
                (o.*m)();
            }
        };

        class Launcher
        {
        public:

        private:
            Y_Disable_Copy_And_Assign(Launcher);
        };

    }

}

#endif // !Y_Concurrent_Thread_Launcher_Included
