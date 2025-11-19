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

        //______________________________________________________________________
        //
        //
        //
        //! hold a persistent object with its method and call function
        //
        //
        //______________________________________________________________________
        class ThreadData : public Runnable
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            typedef void (ThreadData::*Meth)(void); //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! \param o persistent object \param m method pointer
            template <typename OBJECT,typename METHOD> inline
            explicit ThreadData(OBJECT &o, METHOD m) noexcept :
            mine( & ThreadData::call<OBJECT,METHOD> ),
            host( &o ),
            wksp()
            {
                *Memory::Stealth::Cast<METHOD>( Y_Memory_BZero(wksp) ) = m;
            }

            //! cleanup
            virtual ~ThreadData() noexcept;

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void run() noexcept; //!< call object.method()

            //__________________________________________________________________
            //
            //
            // Method
            //
            //__________________________________________________________________
        protected:
            Runnable & self() noexcept; //!< \return *this

        private:
            Y_Disable_Copy_And_Assign(ThreadData);               //!< discarding
            Meth   const mine;                                   //!< pointing to the proper call<OBJECT,METHOD>
            void * const host;                                   //!< object address
            void *       wksp[Alignment::WordsFor<Meth>::Count]; //!< holds method

            //! forged call method
            template <typename OBJECT, typename METHOD> inline
            void call() {
                OBJECT &     o = *Memory::Stealth::Cast<OBJECT>(host);
                METHOD const m = *Memory::Stealth::Cast<METHOD>(wksp);
                (o.*m)();
            }

        };

        //______________________________________________________________________
        //
        //
        //
        //! Lauch object.method() in thread
        //
        //
        //______________________________________________________________________
        class Launch : public ThreadData, public Thread
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! \param o persistent object \param m method pointer
            template <typename OBJECT,typename METHOD> inline
            explicit Launch(OBJECT &o, METHOD m)  :
            ThreadData(o,m),
            Thread( self() )
            {
            }

            //! cleanup
            virtual ~Launch() noexcept;

        private:
            Y_Disable_Copy_And_Assign(Launch); //!< discarding
        };

    }

}

#endif // !Y_Concurrent_Thread_Launch_Included
