
//! \file

#ifndef Y_Apex_Seal_Included
#define Y_Apex_Seal_Included 1

#include "y/ability/lockable.hpp"


namespace Yttrium
{

    namespace Apex
    {

        class Shield : public Lockable
        {
        public:
            explicit Shield();
            virtual ~Shield() noexcept;

        private:
            Y_Disable_Copy_And_Assign(Shield);
            void * const jmutex;

            virtual void doLock()   noexcept;
            virtual void doUnlock() noexcept;
        };

    }

}

#endif

