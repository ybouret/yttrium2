//! \file

#ifndef Y_Concurrent_Thread_Included
#define Y_Concurrent_Thread_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        //! global locking output
#define Y_Thread_Message(MSG) do { Y_Giant_Lock(); (std::cerr << MSG << std::endl).flush(); } while(false)

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

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________
            bool assign(const size_t) noexcept; //!< \return true if was assigned to CPU

        private:
            Y_Disable_Copy_And_Assign(Thread); //!< discarding
            Code * const code;                 //!< internal code
        };


    }

}

#endif // !Y_Concurrent_Thread_Included

