//! \file

#ifndef Y_Concurrent_Thread_Launch_Included
#define Y_Concurrent_Thread_Launch_Included 1

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
                *Memory::Stealth::Cast<METHOD>( Y_Memory_BZero(wksp) ) = m;
            }

            virtual ~ThreadData() noexcept;
            virtual void run() noexcept;

        protected:
            Runnable & self() noexcept;

        private:
            Y_Disable_Copy_And_Assign(ThreadData);
            Meth   const mine;
            void * const host;
            void *       wksp[Alignment::WordsFor<Meth>::Count];

            template <typename OBJECT, typename METHOD> inline
            void call() {
                OBJECT &     o = *Memory::Stealth::Cast<OBJECT>(host);
                METHOD const m = *Memory::Stealth::Cast<METHOD>(wksp);
                (o.*m)();
            }


        };

        class Launch : public ThreadData, public Thread
        {
        public:
            template <typename OBJECT,typename METHOD> inline
            explicit Launch(OBJECT &o, METHOD m)  :
            ThreadData(o,m),
            Thread( self() )
            {
            }

            virtual ~Launch() noexcept;
        private:
            Y_Disable_Copy_And_Assign(Launch);
        };

    }

}

#endif // !Y_Concurrent_Thread_Launch_Included
