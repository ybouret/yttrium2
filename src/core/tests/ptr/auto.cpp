
#include "y/pointer/auto.hpp"
#include "y/utest/run.hpp"
#include "y/concurrent/fake-lock.hpp"
#include "y/pointer/flash-lock.hpp"
#include "y/object.hpp"

using namespace Yttrium;


namespace
{
    class Dummy : public Object, public Concurrent::FakeLock
    {
    public:

        explicit Dummy() noexcept : Object(), Concurrent::FakeLock()
        {
        }

        virtual ~Dummy() noexcept
        {
        }

        void method()
        {
            //std::cerr << "Method With FakeLock!" << std::endl;
            std::cerr << "Method with with #lock=" << count << std::endl;
        }

    private:
        Y_Disable_Copy_And_Assign(Dummy);
    };
}

Y_UTEST(ptr_auto)
{
    AutoPtr<int> ip; std::cerr << ip << std::endl;
    ip = new int(4); std::cerr << ip << std::endl;

    {
        AutoPtr<Dummy,FlashLock> p;
        p = new Dummy();
        p->method();
    }

}
Y_UDONE()
