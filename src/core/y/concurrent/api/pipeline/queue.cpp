#include "y/concurrent/api/pipeline/queue.hpp"
#include "y/type/destroy.hpp"

namespace Yttrium
{
    namespace Concurrent
    {
        class Queue:: Code : public Object
        {
        public:
            inline explicit Code(const size_t n)
            {
            }

            inline virtual ~Code() noexcept
            {
            }

        private:
            Y_Disable_Copy_And_Assign(Code);
        };


        const char * const Queue:: CallSign = "Concurrent::Queue";

        Queue:: Queue(const size_t n) :
        Pipeline(n,CallSign),
        code( new Code(n) )
        {
        }

        Queue:: ~Queue() noexcept
        {
            assert(code);
            Destroy(code);
        }

    }

}
