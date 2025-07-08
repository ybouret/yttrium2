//! \file

#ifndef Y_Apex_JMutex_Included
#define Y_Apex_JMutex_Included 1

#include "y/object.hpp"
#include "y/concurrent/mutex.hpp"


namespace Yttrium
{
    
    namespace Apex
    {
        //! Joint Mutex
        class JointMutex : public Object, public Concurrent::Mutex
        {
        public:
            explicit JointMutex();           //!< setup
            virtual ~JointMutex() noexcept;  //!< cleanu[
            JointMutex *next;                //!< for list
            JointMutex *prev;                //!< for list
        private:
            Y_Disable_Copy_And_Assign(JointMutex); //!< discarding
        };
    }
}

#endif


