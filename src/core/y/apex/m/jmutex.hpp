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
        class JMutex : public Object, public Concurrent::Mutex
        {
        public:
            explicit JMutex();
            virtual ~JMutex() noexcept;
            
            JMutex *next;
            JMutex *prev;
        private:
            Y_Disable_Copy_And_Assign(JMutex);
        };
    }
}

#endif


