
#include "y/singleton.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

namespace {

    class MySingle : public Singleton<MySingle,GiantLockPolicy>
    {
    public:
        static const char * const CallSign;
        static const Longevity    LifeTime = GreatestLifeTime - 19;
    private:
        Y_Disable_Copy_And_Assign(MySingle);
        friend class Singleton<MySingle,GiantLockPolicy>;

        explicit MySingle()
        {

        }

        virtual ~MySingle() noexcept
        {

        }
    };

    const char * const MySingle:: CallSign = "MySingle";

}

Y_UTEST(singleton)
{
    Concurrent::Singulet::Verbose  = true;

    MySingle &mine = MySingle::Instance();

    std::cerr << "mine=" << mine.callSign() << std::endl;

}
Y_UDONE()

