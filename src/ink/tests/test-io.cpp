

#include "y/ink/image/format/bmp.hpp"

#include "y/color/rgba.hpp"
#include "y/utest/run.hpp"
#include "y/concurrent/api/simd/crew.hpp"
#include "y/concurrent/api/simd/sole.hpp"
#include "y/color/gray.hpp"
#include "y/random/park-miller.hpp"
#include "y/random/fill.hpp"

using namespace Yttrium;



Y_UTEST(io)
{
    Random::ParkMiller ran;
#if 0
    Concurrent::Processor cpus = new Concurrent::Crew( Concurrent::Site::Default );
    Concurrent::Processor cpu1 = new Concurrent::Sole();
    Ink::Broker           par(cpus);
    Ink::Broker           seq(cpu1);
#endif

    Ink::FormatBMP  bmp; bmp.renderExtension();
    Ink::Image      pxm(80,60);
    for(size_t j=0;j<pxm.h;++j)
    {
        for(size_t i=0;i<pxm.w;++i)
        {
            Ink::RGB  c;
            Random::Fill::Block(ran,&c,sizeof(c));
            pxm[j][i] = c;
        }
    }

    bmp.save(pxm,"image.bmp",0);
    



}
Y_UDONE()

