

#include "y/ink/ops/getmax.hpp"
#include "y/utest/run.hpp"
#include "y/concurrent/api/simd/crew.hpp"
#include "y/concurrent/api/simd/sole.hpp"

#include "y/ink/image/formats.hpp"

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

        {
            Ink::Pixmap<float> pxmf(image.w,image.w);
            //Ink::Ops::Convert(par,pxmf,RGBA2GSF,image);
        }

    }



}
Y_UDONE()

