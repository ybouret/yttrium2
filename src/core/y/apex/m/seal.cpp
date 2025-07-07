
#include "y/apex/m/seal.hpp"
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

        Seal:: Seal() : jmutex( QueryJointMutex() )
        {

        }

        Seal:: ~Seal() noexcept
        {
            static Archon & archon = Archon::Location();
            archon.storeMutex( static_cast<JointMutex *>(jmutex) );
            Coerce(jmutex) = 0;
        }

        void Seal:: doLock() noexcept
        {
            assert(jmutex);
            static_cast<JointMutex *>(jmutex)->lock();
        }

        void Seal:: doUnlock() noexcept
        {
            assert(jmutex);
            static_cast<JointMutex *>(jmutex)->unlock();
        }
    }

}

