

#include "y/concurrent/api/pipeline/alone.hpp"
#include "y/pointer/auto.hpp"
#include "y/type/destroy.hpp"
#include "y/concurrent/fake-lock.hpp"

namespace Yttrium
{
    namespace Concurrent
    {

        const char * const Alone:: CallSign = "Concurrent::Alone";

        class Alone:: Code : public Object
        {
        public:
            explicit Code() noexcept : fakeLock(), context(fakeLock,1,0)
            {
            }

            virtual ~Code() noexcept
            {
            }

            FakeLock      fakeLock;
            const Context context;

        private:
            Y_Disable_Copy_And_Assign(Code);
        };

        Alone:: Alone() :
        Pipeline(1,CallSign),
        code( new Code() )
        {
        }

        Alone:: ~Alone() noexcept
        {
            assert(code);
            Destroy(code);
        }

        const char * Alone:: callSign() const noexcept
        {
            return CallSign;
        }
        
    }

}
