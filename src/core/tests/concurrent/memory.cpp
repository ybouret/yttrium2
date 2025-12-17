#include "y/concurrent/api/simd/crew.hpp"
#include "y/utest/run.hpp"

using namespace Yttrium;

namespace
{
    class ParaMem
    {
    public:
        explicit ParaMem() : result(0), kernel( I(), & ParaMem::run)
        {
        }

        virtual ~ParaMem() noexcept
        {
        }

        Concurrent::Kernel & operator*() noexcept { return kernel; }


    private:
        Y_Disable_Copy_And_Assign(ParaMem);
        int                result;
        Concurrent::Kernel kernel;

        inline ParaMem * I() noexcept { return this; }

        void run(const Concurrent::Context &ctx)
        {
            { Y_Giant_Lock(); ( std::cerr << "in " << ctx << std::endl).flush() ; }

        }
    };
}

Y_UTEST(concurrent_memory)
{
    ParaMem mem;

    Concurrent::Crew crew( Concurrent::Site::Default );
    crew( *mem );

}
Y_UDONE()
