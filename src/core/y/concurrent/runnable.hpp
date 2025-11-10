
//! \file

#ifndef Y_Concurrent_Runnable_Included
#define Y_Concurrent_Runnable_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        //______________________________________________________________________
        //
        //
        //
        //! Simple runnable interface
        //
        //
        //______________________________________________________________________
        class Runnable
        {
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
        protected:
            explicit Runnable() noexcept; //!< setup

        public:
            virtual ~Runnable() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void run() noexcept = 0; //!< to be run in parallel

        private:
            Y_Disable_Copy_And_Assign(Runnable); //!< discarding
        };
    }

}

#endif // !Y_Concurrent_Runnable_Included

