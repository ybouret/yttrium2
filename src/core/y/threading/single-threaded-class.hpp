
//! \file

#ifndef Y_Single_Threaded_Class_Included
#define Y_Single_Threaded_Class_Included 1

#include "y/core/setup.hpp"
#include "y/threading/must-lock.hpp"

namespace Yttrium
{
    //__________________________________________________________________________
    //
    //
    //
    //! no locking for Single-Threaded Classes
    //
    //
    //__________________________________________________________________________
    class SingleThreadedClass
    {
    public:

        //! dummy lock
        class Lock
        {
        public:
            Lock(const SingleThreadedClass &) noexcept; //!< do nothing
            ~Lock() noexcept;                           //!< do nothing
        private:
            Y_Disable_Copy_And_Assign(Lock); //!< discarding
        };

        explicit SingleThreadedClass() noexcept; //!< setup
        virtual ~SingleThreadedClass() noexcept; //!< cleanup


    private:
        Y_Disable_Copy_And_Assign(SingleThreadedClass); //!< discarding
    };
}

#endif

