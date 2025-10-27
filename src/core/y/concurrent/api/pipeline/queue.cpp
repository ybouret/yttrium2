#include "y/concurrent/api/pipeline/queue.hpp"
#include "y/type/destroy.hpp"
#include "y/concurrent/thread.hpp"
#include "y/object/school-of.hpp"
#include "y/concurrent/condition.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        class Queue:: Player : public Thread
        {
        public:

            inline explicit Player(Proc proc, void * const args) :
            Thread(proc,args)
            {
            }

            inline virtual ~Player() noexcept {}

        private:
            Y_Disable_Copy_And_Assign(Player);
        };



        class Queue:: Coach : public Object
        {
        public:
            inline explicit Coach(const size_t n) :
            size(n),
            built(0),
            ready(0),
            mutex(),
            synch(),
            team(size)
            {
                try {
                    init();
                }
                catch(...)
                {
                    quit();
                    throw;
                }
            }

            inline virtual ~Coach() noexcept
            {
                quit();
            }

            const size_t             size;
            size_t                   built;
            size_t                   ready;
            Mutex                    mutex;
            Condition                synch;
            Memory::SchoolOf<Player> team;

        private:
            Y_Disable_Copy_And_Assign(Coach);
            static void Launch(void * const) noexcept;
            void init();
            void quit() noexcept;
        };


        void Queue:: Coach:: Launch(void * const args) noexcept
        {

        }

        void Queue:: Coach:: init()
        {

        }

        void Queue:: Coach:: quit() noexcept
        {

        }


        const char * const Queue:: CallSign = "Concurrent::Queue";

        Queue:: Queue(const size_t n) :
        Pipeline(n,CallSign),
        coach( new Coach(n) )
        {
            //std::cerr << "sizeof(Coach)=" << sizeof(Coach) << std::endl;
        }

        Queue:: ~Queue() noexcept
        {
            assert(coach);
            Destroy(coach);
        }

    }

}
