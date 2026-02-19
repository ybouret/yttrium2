
#include "y/ink/ops/ld.hpp"
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

        for(unit_t k=tile.h;k>0;--k)
        {
            const Ink::Segment    s   = tile[k];
            typename PIXMAP::Row &row = pxm[s.start.y];
            for(unit_t i=s.width,x=s.start.x;i>0;--i,++x)
            {
                row[x] = 0;
            }
        }
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

    Ink::LoadPixel::Set(par,pxm,1.0f);

    


}
Y_UDONE()

