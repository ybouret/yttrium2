

#include "y/ink/ops/getmax.hpp"
#include "y/ink/ops/getmin.hpp"
#include "y/utest/run.hpp"
#include "y/concurrent/api/simd/crew.hpp"
#include "y/concurrent/api/simd/sole.hpp"

#include "y/ink/image/formats.hpp"
#include "y/color/conversion.hpp"
#include "y/color/ramp.hpp"
#include "y/color/x11.hpp"


using namespace Yttrium;


namespace {
    static const Color::RGBA32 table[] = { Y_Blue, Y_Green, Y_Red };
}



Y_UTEST(max)
{
    Concurrent::Processor cpus = new Concurrent::Crew( Concurrent::Site::Default );
    Concurrent::Processor cpu1 = new Concurrent::Sole();
    Ink::Broker           par(cpus);
    Ink::Broker           seq(cpu1);
    Ink::Formats &        IMG = Ink::Formats::Std();
    const Color::Ramp     ramp("ramp",table,sizeof(table)/sizeof(table[0]));

    if(argc>1)
    {
        Ink::Image         image = IMG.load(argv[1],0);
        IMG.save(image,"img.png",0);

        {
            Ink::Pixmap<float> pxmf(image.w,image.w);
            Ink::Ops::Convert(par,pxmf,Color::Convert::RGBATo<float>,image);
            IMG.save(par,Color::Convert::ToRGBA<float>,pxmf,"gsf.png",0);
            const float vmax = Ink::GetMax::Of(par,pxmf);
            const float vmin = Ink::GetMin::Of(par,pxmf);
            std::cerr << "vmin=" << vmin << std::endl;
            std::cerr << "vmax=" << vmax << std::endl;
            Color::RampOf<float> rmp(ramp,vmin,vmax);
            IMG.save(seq,rmp,pxmf,"max.png",0);
        }

    }



}
Y_UDONE()

