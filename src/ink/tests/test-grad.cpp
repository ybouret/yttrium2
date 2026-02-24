
#include "y/ink/filter/gradient.hpp"
#include "y/ink/image/formats.hpp"
#include "y/utest/run.hpp"

#include "y/ink/filter/prewitt3.hpp"

using namespace Yttrium;
using namespace Ink;

#include "y/color/x11.hpp"
#include "y/concurrent/api/simd/crew.hpp"
#include "y/color/conversion.hpp"

namespace
{
    static const Color::RGBA32 table2[] = { Y_Black, Y_Orange, Y_White };

}

Y_UTEST(grad)
{
    Concurrent::Processor cpus = new Concurrent::Crew( Concurrent::Site::Default );
    Ink::Broker           broker(cpus);
    const Color::Ramp     ramp2(Y_Color_Ramp_From(table2));

    Filter<float> F( Y_Filter_From(Prewitt3) );
    std::cerr << F << std::endl;

    Formats &IMG = Formats::Std();
    if(argc>1)
    {
        Image           img = IMG.load(argv[1],0);
        Pixmap<float>   gsf(img.w,img.h);

        Ops::Convert(broker,gsf,Color::Convert::RGBATo<float>, img);

        Gradient<float> g(img.w,img.h);
        FilterGradient<float>::Compute(broker,g,F,gsf);


        std::cerr << "Saving..." << std::endl;
        IMG.save(img,"img.png",0);
        IMG.save(broker,Color::Convert::ToRGBA<float>,gsf, "gsf.png", 0);
        IMG.save(ramp2,broker,g, "gsf-grad.png", 0);

    }


}
Y_UDONE()
