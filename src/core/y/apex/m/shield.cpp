
#include "y/apex/m/shield.hpp"
#include "y/apex/m/archon.hpp"


namespace Yttrium
{

    namespace Apex
    {

        namespace
        {
            static void * QueryJointMutex()
            {
                static Archon &archon = Archon::Instance();
                return archon.queryMutex();
            }

        }

        Shield:: Shield() : jmutex( QueryJointMutex() )
        {

        }

        Shield:: ~Shield() noexcept
        {
            static Archon & archon = Archon::Location();
            archon.storeMutex( static_cast<JointMutex *>(jmutex) );
            Coerce(jmutex) = 0;
        }

        void Shield:: doLock() noexcept
        {
            assert(jmutex);
            static_cast<JointMutex *>(jmutex)->lock();
        }

        void Shield:: doUnlock() noexcept
        {
            assert(jmutex);
            static_cast<JointMutex *>(jmutex)->unlock();
        }
    }

}

