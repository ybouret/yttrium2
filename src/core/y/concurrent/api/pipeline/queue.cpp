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
            Thread(proc,args),
            next(0),
            prev(0)
            {
                Y_Thread_Message("in player");
            }

            inline virtual ~Player() noexcept {}

            Player *next;
            Player *prev;

        private:
            Y_Disable_Copy_And_Assign(Player);
        };



        class Queue:: Coach : public Object
        {
        public:
            inline explicit Coach(const size_t n) :
            size(n),
            ready(0),
            built(0),
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
            size_t                   ready;
            size_t                   built;
            Mutex                    mutex;
            Condition                stop;
            Condition                sync;
            Memory::SchoolOf<Player> team;

        private:
            Y_Disable_Copy_And_Assign(Coach);
            static void Launch(void * const) noexcept;
            void        init();
            void        quit() noexcept;
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
                ++built;
                mutex.lock();
                if(ready<built)
                {
                    sync.wait(mutex);
                    assert(ready==built);
                }
                mutex.unlock();
            }
            std::cerr << "all built" << std::endl;
        }

        void Queue:: Coach:: quit() noexcept
        {
            std::cerr << "quit" << std::endl;
            stop.broadcast();

            while(built>0) {
                Destruct(team.entry+(--built));
            }
        }

        void Queue:: Coach:: run() noexcept
        {
            // entering a new thread
            mutex.lock();

            // setup
            const Context ctx(mutex,size,ready);
            Y_Thread_Message("ready=" << ready);


            // synchronize
            ++ready;
            sync.broadcast();

            // wait on a lock mutex
            stop.wait(mutex);

            // wake up on a locked mutex
            {
                Y_Thread_Message("leaving " << ctx);
            }
            mutex.unlock();
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

        const char * Queue:: callSign() const noexcept
        {
            return CallSign;
        }

    }

}
