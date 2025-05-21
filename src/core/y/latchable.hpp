
//! \file

#ifndef Y_Latchable_Included
#define Y_Latchable_Included 1

#include "y/lockable.hpp"


namespace Yttrium
{

    class Latchable : public Lockable
    {
    protected:
        explicit Latchable() noexcept;
    public:
        virtual ~Latchable() noexcept;

        bool tryLock() noexcept;

    private:
        Y_Disable_Copy_And_Assign(Latchable);
        virtual bool doTryLock() noexcept = 0;
    };

#define Y_Latchable_Decl() virtual bool doTryLock() noexcept
}

#endif

