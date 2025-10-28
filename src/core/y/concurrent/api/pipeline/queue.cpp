#include "y/concurrent/api/pipeline/queue.hpp"
#include "y/type/destroy.hpp"
#include "y/type/destruct.hpp"
#include "y/concurrent/thread.hpp"
#include "y/object/school-of.hpp"
#include "y/concurrent/condition.hpp"

#include <iostream>

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

            void run() noexcept;

            const size_t             size;
            size_t                   built;
            size_t                   ready;
            Mutex                    mutex;
            Condition                stop;
            Condition                wait;
            Memory::SchoolOf<Player> team;

        private:
            Y_Disable_Copy_And_Assign(Coach);
            static void Launch(void * const) noexcept;
            void init();
            void quit() noexcept;
        };


        void Queue:: Coach:: Launch(void * const args) noexcept
        {
            assert(args);
            static_cast<Coach *>(args)->run();
        }

        void Queue:: Coach:: init()
        {
            while(built<size)
            {
                new (team.entry+built) Player(Launch,this);
            }
        }

        void Queue:: Coach:: quit() noexcept
        {
            while(built>0) {
                Destruct(team.entry+(--built));
            }
        }

        void Queue:: Coach:: run() noexcept
        {
            // entering a new thread @built
            mutex.lock();
            const Context ctx(mutex,size,built);
            Y_Thread_Message("built=" << built);

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
