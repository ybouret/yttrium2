
//! \file

#ifndef Y_Apex_Seal_Included
#define Y_Apex_Seal_Included 1

#include "y/ability/lockable.hpp"


namespace Yttrium
{

    namespace Apex
    {

        //______________________________________________________________________
        //
        //
        //
        //! wrapper for JointMutex I/O
        //
        //
        //______________________________________________________________________
        class Shield : public Lockable
        {
        public:
            explicit Shield();          //!< setup
            virtual ~Shield() noexcept; //!< cleanup

        private:
            Y_Disable_Copy_And_Assign(Shield); //!< discarding
            void * const jmutex;               //!< JointMutex address

            virtual void doLock()   noexcept;
            virtual void doUnlock() noexcept;
        };

    }

}

#endif

