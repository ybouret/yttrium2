
#include "y/concurrent/api/pipeline.hpp"


#include "y/utest/run.hpp"

#include "y/pointer/arc.hpp"
#include "y/container/sequence/vector.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        typedef ArcPtr<Pipeline> Appliance;

        template <typename ENGINE>
        class Asynchronous
        {
        public:

            inline Asynchronous(Appliance &app) :
            appliance(app),
            engines(app->size())
            {
            }


            inline virtual ~Asynchronous() noexcept
            {
            }

        protected:
            Appliance      appliance;
            Vector<ENGINE> engines;

        private:
            Y_Disable_Copy_And_Assign(Asynchronous);
        };

    }
}

using namespace Yttrium;



Y_UTEST(concurrent_invoke)
{

}
Y_UDONE()

