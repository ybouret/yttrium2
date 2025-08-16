#include "y/concurrent/api/simd/crew.hpp"
#include "y/concurrent/api/simd/sole.hpp"
#include "y/utest/run.hpp"
#include "y/ascii/convert.hpp"
#include "y/string/env.hpp"
#include "y/container/cxx/array.hpp"
#include "y/concurrent/split/1d.hpp"

using namespace Yttrium;

namespace
{

    class Compute
    {
    public:
        explicit Compute(const size_t maxIndex,
                         const size_t maxProcs) :
        nmax(maxIndex),
        part(maxProcs)
        {
        }

        virtual ~Compute() noexcept
        {
        }

        inline void Run(const Concurrent::Context &ctx)
        {
        }

        const size_t     nmax;
        CxxArray<double> part;

    private:
        Y_Disable_Copy_And_Assign(Compute);
    };

    void DoSomething(const Concurrent::Context &ctx)
    {
        Y_Lock(ctx.sync);
        (std::cerr << "DoSomething in " << ctx << std::endl).flush();
    }
}

Y_UTEST(concurrent_simd)
{
    Concurrent::SIMD::Verbose = Environment::Flag("VERBOSE");
    size_t n = 1;
    if(argc>1) n = ASCII::Convert::To<size_t>(argv[1],"n");

    Compute compute(10000,n);
    Concurrent::Crew         crew(n);
    Concurrent::Sole         sole;
    Concurrent::SIMD::Kernel code = cfunctor(DoSomething);
    Concurrent::SIMD::Kernel code2( &compute, & Compute::Run );

    sole(code);
    crew(code);

}
Y_UDONE()

