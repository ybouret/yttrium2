
//! \file

#ifndef Y_Apex_Shield_Included
#define Y_Apex_Shield_Included 1

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
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Shield();          //!< setup
            virtual ~Shield() noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Interface
            //
            //__________________________________________________________________
            virtual void lock()   noexcept;
            virtual void unlock() noexcept;

        private:
            Y_Disable_Copy_And_Assign(Shield); //!< discarding
            void * const jmutex;               //!< JointMutex address

        };

    }

}

#endif // !Y_Apex_Shield_Included

