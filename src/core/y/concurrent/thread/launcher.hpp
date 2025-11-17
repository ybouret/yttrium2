//! \file

#ifndef Y_Concurrent_Thread_Launcher_Included
#define Y_Concurrent_Thread_Launcher_Included 1

#include "y/concurrent/thread.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        template <typename OBJECT, typename METHOD>
        class ThreadData
        {
        public:

            inline explicit ThreadData(OBJECT &theObject,
                                       METHOD  theMethod) noexcept :
            host(theObject),
            meth(theMethod)
            {
            }


            inline virtual ~ThreadData() noexcept {}


        protected:
            OBJECT &host;
            METHOD  meth;

            inline void  call() noexcept {
                try { (host.*meth)(); } catch(...) {}
            }

        private:
            Y_Disable_Copy_And_Assign(ThreadData);
        };

        template <typename OBJECT, typename METHOD>
        class Launcher : public ThreadData<OBJECT,METHOD>, public Thread
        {
        public:
            typedef ThreadData<OBJECT,METHOD> DataType;

            inline explicit Launcher(OBJECT &theObject,
                              METHOD  theMethod) :
            DataType(theObject,theMethod),
            Thread(Call,this)
            {
            }

            inline virtual ~Launcher() noexcept {}

        private:
            Y_Disable_Copy_And_Assign(Launcher);
            static inline void Call(void * const args) noexcept
            {
                assert(args);
                static_cast<Launcher *>(args)->call();
            }
        };


    }

}

#endif // !Y_Concurrent_Thread_Launcher_Included
