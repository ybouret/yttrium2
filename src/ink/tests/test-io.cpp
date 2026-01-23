

#include "y/ink/image/format/bmp.hpp"
#include "y/ink/image/format/pnm.hpp"
#include "y/ink/image/format/jpeg.hpp"

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

    Ink::FormatBMP   bmp; bmp.renderExtension();
    Ink::FormatPNM   pnm; pnm.renderExtension();
    Ink::FormatJPEG  jpg; jpg.renderExtension();


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
    {
        Ink::Image reloaded = bmp.load("image.bmp",0);
        Y_ASSERT(reloaded.width==pxm.width);
    }

    pnm.save(pxm,"image.pbm",0);
    pnm.save(pxm,"image.pgm",0);
    pnm.save(pxm,"image.ppm",0);
    jpg.save(pxm,"image.jpg",0);
    




}
Y_UDONE()

