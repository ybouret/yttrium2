
#include "y/singleton.hpp"
#include "y/memory/management/dead-pool.hpp"
#include "y/utest/run.hpp"
#include "y/system/rand.hpp"
#include "y/memory/stealth.hpp"


namespace Yttrium
{
    namespace Memory
    {

        template <typename T, System::AtExit::Longevity LIFE_TIME>
        class Netherworld  : public Singleton<Netherworld<T,LIFE_TIME>,ClassLockPolicy>
        {
        public:
            

        private:
            Y_Disable_Copy_And_Assign(Netherworld);

            DeadPool deadPool;
        };

    }
}
using namespace Yttrium;


Y_UTEST(memory_netherworld)
{

}
Y_UDONE()

