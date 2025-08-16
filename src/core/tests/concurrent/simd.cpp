#include "y/concurrent/api/simd/crew.hpp"
#include "y/concurrent/api/simd/sole.hpp"
#include "y/utest/run.hpp"
#include "y/ascii/convert.hpp"
#include "y/string/env.hpp"

using namespace Yttrium;

namespace
{
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

    Concurrent::Crew         crew(n);
    Concurrent::Sole         sole;
    Concurrent::SIMD::Kernel code = cfunctor(DoSomething);

    sole(code);
    crew(code);

}
Y_UDONE()

