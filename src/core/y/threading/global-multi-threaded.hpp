//! \file

#ifndef Y_GlobalMultiThreaded_Included
#define Y_GlobalMultiThreaded_Included 1

#include "y/threading/locker.hpp"

namespace Yttrium {

    class Lockable;

    class GlobalMultiThreaded
    {
    public:
        typedef Threading::Locker<GlobalMultiThreaded> Lock;

        explicit GlobalMultiThreaded();
        virtual ~GlobalMultiThreaded() noexcept;

    private:
        Y_Disable_Copy_And_Assign(GlobalMultiThreaded);
        friend class Threading::Locker<GlobalMultiThreaded>;
        Lockable * const authorization;
    };

}
#endif

