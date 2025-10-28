
//! \file

#ifndef Y_Concurrent_Task_Included
#define Y_Concurrent_Task_Included 1

#include "y/concurrent/api/kernel.hpp"
#include "y/core/linked/list/cxx.hpp"

namespace Yttrium
{
    namespace Concurrent
    {


        class Task : public Kernel
        {
        public:
            typedef uint32_t ID;

            template <typename CALLABLE> inline
            explicit Task(const CALLABLE &fcn,
                          const ID        tid) :
            Kernel(fcn),
            uuid(tid),
            next(0),
            prev(0)
            {
            }

            template <typename OBJECT, typename METHOD> inline
            explicit Task(OBJECT & host,
                          METHOD   meth,
                          const ID tid) :
            Kernel(&host,meth),
            uuid(tid),
            next(0),
            prev(0)
            {
            }


            void perform(const Context &ctx) noexcept;

            virtual ~Task() noexcept;


            const uint32_t uuid;
            Task *         next;
            Task *         prev;

        private:
            Y_Disable_Copy_And_Assign(Task);
        };

        typedef CxxListOf<Task> Tasks;

    }

}

#endif // !Y_Concurrent_Task_Included
