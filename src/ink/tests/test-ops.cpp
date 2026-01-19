
#include "y/ink/ops.hpp"
#include "y/utest/run.hpp"
#include "y/concurrent/api/simd/crew.hpp"
#include "y/concurrent/api/simd/sole.hpp"

using namespace Yttrium;

namespace
{
    template <typename PIXMAP>
    static inline void DoSomething(Lockable  &,
                                   Ink::Tile &tile,
                                   PIXMAP    &pxm)
    {
        { Y_Giant_Lock(); std::cerr << "on " << tile << std::endl; }
    }
}

Y_UTEST(ops)
{
    Concurrent::Processor cpus = new Concurrent::Crew( Concurrent::Site::Default );
    Concurrent::Processor cpu1 = new Concurrent::Sole();
    Ink::Broker           par(cpus);
    Ink::Broker           seq(cpu1);
    Ink::Pixmap<float>    pxm(100,200);

    Ink::Ops::Apply(seq,DoSomething< Ink::Pixmap<float> >,pxm);
    Ink::Ops::Apply(par,DoSomething< Ink::Pixmap<float> >,pxm);


}
Y_UDONE()

