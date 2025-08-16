#include "y/concurrent/api/simd/crew.hpp"
#include "y/concurrent/api/simd/sole.hpp"
#include "y/utest/run.hpp"
#include "y/ascii/convert.hpp"
#include "y/string/env.hpp"
#include "y/container/cxx/array.hpp"
#include "y/concurrent/split/1d.hpp"
#include "y/system/wall-time.hpp"
#include "y/apex/rational.hpp"
#include <cmath>

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
            Concurrent::Split::In1D in1d(nmax);
            Concurrent::Split::Zone zone = in1d(ctx,1);
            double &sum = part[ctx.indx];

            sum = 0;
            for(size_t n=zone.offset,i=zone.length;i>0;--i,++n)
            {
                sum += 1.0 / (double)(n*n);
            }
        }

        double get()
        {
            double sum = 0;
            for(size_t i=part.size();i>0;--i) sum += part[i];
            sum *= 6.0;
            return sqrt(sum);
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

    Compute compute(10000000,n);
    Concurrent::Crew         crew(n);
    Concurrent::Sole         sole;
    Concurrent::SIMD::Kernel code = cfunctor(DoSomething);
    Concurrent::SIMD::Kernel code2( &compute, & Compute::Run );

    sole(code);
    crew(code);

    System::WallTime chrono;


    uint64_t mark = chrono.Ticks();
    compute.part.ld(0);
    sole(code2);
    const apn soleEll =  chrono.Ticks() - mark;
    std::cerr << compute.get() << std::endl;


    mark = chrono.Ticks();
    compute.part.ld(0);
    crew(code2);
    const apn crewEll =  chrono.Ticks() - mark;
    std::cerr << compute.get() << std::endl;

    const apq rho(Positive,soleEll,crewEll);
    std::cerr << "rho=" << rho.to<double>() << std::endl;
}
Y_UDONE()

