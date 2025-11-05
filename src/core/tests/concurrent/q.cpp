#include "y/concurrent/thread/site.hpp"
#include "y/concurrent/thread.hpp"
#include "y/concurrent/mutex.hpp"
#include "y/concurrent/condition.hpp"
#include "y/concurrent/api/kernel.hpp"
#include "y/container/cxx/series.hpp"
#include "y/core/linked/list/raw.hpp"

#include "y/utest/run.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        class Leader
        {
        public:

            inline explicit Leader(const size_t sz) :
            mutex(), chief(), size(sz)
            {
            }


            inline virtual ~Leader() noexcept
            {
            }

            Mutex        mutex;
            Condition    chief;
            const size_t size;

        private:
            Y_Disable_Copy_And_Assign(Leader);
        };

        class Worker : public Context
        {
        public:

            inline explicit Worker(Leader &     ld,
                                   const size_t rk) :
            Context(ld.mutex,ld.size,rk),
            mutex(ld.mutex),
            chief(ld.chief)
            {
            }

            Mutex     & mutex;
            Condition & chief;


        private:
            Y_Disable_Copy_And_Assign(Worker);
        };

        class Brigade : public Leader
        {
        public:

        private:
            Y_Disable_Copy_And_Assign(Brigade);
        };



    }
}

using namespace Yttrium;

Y_UTEST(concurrent_q)
{
    //Concurrent::Team team( Concurrent::Site::Default );
}
Y_UDONE()


