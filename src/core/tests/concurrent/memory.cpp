#include "y/concurrent/api/simd/crew.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

namespace
{
    class ParaMem
    {
    public:
        explicit ParaMem() noexcept
        {
        }

        virtual ~ParaMem() noexcept
        {
        }

    private:
        Y_Disable_Copy_And_Assign(ParaMem);
    };
}

Y_UTEST(concurrent_memory)
{
    Concurrent::Crew crew( Concurrent::Site::Default );
    
}
Y_UDONE()
