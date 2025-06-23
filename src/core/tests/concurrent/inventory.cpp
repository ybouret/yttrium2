#include "y/concurrent/data/inventory.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

namespace
{
    class Dummy
    {
    public:
        static const System::AtExit::Longevity LifeTime = 007;
        static const char * const              CallSign;
        typedef const int ParamType;

        Dummy() noexcept : value(0)
        {
        }

        ~Dummy() noexcept
        {
        }

        Dummy(const Dummy &other) : value(other.value) {}


        const int value;
    private:
        Y_Disable_Assign(Dummy);
    };
    const char * const Dummy:: CallSign = "Dummy";

}

Y_UTEST(concurrent_inventory)
{
    Concurrent::Singulet::Verbose = true;
    Concurrent::Inventory<Dummy> & inventory = Concurrent::Inventory<Dummy>::Instance();
    inventory.display(std::cerr,1);
}
Y_UDONE()

