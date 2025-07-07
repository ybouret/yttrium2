
//! \file

#ifndef Y_Apex_Seal_Included
#define Y_Apex_Seal_Included 1

#include "y/ability/lockable.hpp"


namespace Yttrium
{

    namespace Apex
    {

        class Seal : public Lockable
        {
        public:
            explicit Seal();
            virtual ~Seal() noexcept;

        private:
            Y_Disable_Copy_And_Assign(Seal);
            void * const jmutex;

            virtual void doLock()   noexcept;
            virtual void doUnlock() noexcept;
        };

    }

}

#endif

