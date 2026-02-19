

#include "y/ink/ops/getmax.hpp"
#include "y/utest/run.hpp"
#include "y/concurrent/api/simd/crew.hpp"
#include "y/concurrent/api/simd/sole.hpp"

#include "y/ink/image/formats.hpp"
#include "y/color/conversion.hpp"

#include "y/ink/ops.hpp"

using namespace Yttrium;


namespace Yttrium
{
    namespace Ink
    {
        
      
    }
}



Y_UTEST(max)
{
    Concurrent::Processor cpus = new Concurrent::Crew( Concurrent::Site::Default );
    Concurrent::Processor cpu1 = new Concurrent::Sole();
    Ink::Broker           par(cpus);
    Ink::Broker           seq(cpu1);

    Ink::Formats &IMG = Ink::Formats::Std();

    if(argc>1)
    {
        Ink::Image         image = IMG.load(argv[1],0);
        IMG.save(image,"img.png",0);

        {
            Ink::Pixmap<float> pxmf(image.w,image.w);
            Ink::Ops::Convert(par,pxmf,Color::Convert::RGBATo<float>,image);
            IMG.saveAs(par,Color::Convert::ToRGBA<float>,pxmf,"gsf.png",0);
            const float vmax = Ink::GetMax::Of(par,pxmf);
            std::cerr << "vmax=" << vmax << std::endl;
        }

    }



}
Y_UDONE()

