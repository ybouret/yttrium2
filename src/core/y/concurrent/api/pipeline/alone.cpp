

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
        Pipeline(),
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


        void Alone:: flush() noexcept
        {
        }

        void Alone:: prune() noexcept
        {

        }

        void Alone:: enqueue(TaskIDs &,const Kernels &kernels)
        {
            assert(code);
            for(Kernels::ConstIterator it=kernels.begin();it!=kernels.end();++it)
            {
                Kernel &k = Coerce(*it);
                k(code->context);
                ++counter;
            }
        }

        size_t Alone:: size() const noexcept
        {
            return 1;
        }
    }

}
