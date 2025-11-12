//! \file

#ifndef Y_Concurrent_Thread_Included
#define Y_Concurrent_Thread_Included 1

#include "y/core/setup.hpp"
#include <cassert>

namespace Yttrium
{
    namespace Concurrent
    {

        //! global locking output
#define Y_Thread_Message(MSG) do { Y_Giant_Lock(); (std::cerr << MSG << std::endl).flush(); } while(false)


        class Runnable;

        //______________________________________________________________________
        //
        //
        //
        //! Thread Execution wraper
        //
        // 
        //______________________________________________________________________
        class Thread
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definitions
            //
            //__________________________________________________________________
            class Launcher;
            class Code;
            typedef void (*Proc)(void * const); //!< alias

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! launch thread
            /**
             \param proc PERSISTENT procedure
             \param args PERSISTENT arguments
             */
            explicit Thread(Proc proc, void * const args);

            //! wait for thread to return
            virtual ~Thread() noexcept;

            explicit Thread(Runnable &);

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            bool assign(const size_t) noexcept; //!< \return true if was assigned to CPU

#if 1
            //! helper to call run() of arguments
            /**
             \param args address of a RUNNABLE with run() method
             */
            template <typename RUNNABLE> static inline
            void Run(void * const args) noexcept
            {
                assert(0!=args);
                static_cast<RUNNABLE *>(args)->run();
            }
#endif
            
        private:
            Y_Disable_Copy_And_Assign(Thread); //!< discarding
            Code * const code;                 //!< internal code
        };


    }

}

#endif // !Y_Concurrent_Thread_Included

