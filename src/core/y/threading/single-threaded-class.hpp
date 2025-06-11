
//! \file

#ifndef Y_Single_Threaded_Class_Included
#define Y_Single_Threaded_Class_Included 1

#include "y/core/setup.hpp"

namespace Yttrium
{
    class SingleThreadedClass
    {
    public:
        class Lock
        {
        public:
            Lock(const SingleThreadedClass &) noexcept;
            ~Lock() noexcept;
        private:
            Y_Disable_Copy_And_Assign(Lock);
        };

        explicit SingleThreadedClass() noexcept;
        virtual ~SingleThreadedClass() noexcept;


    private:
        Y_Disable_Copy_And_Assign(SingleThreadedClass);
    };
}

#endif

