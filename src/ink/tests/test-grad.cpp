
#include "y/ink/filter/gradient.hpp"
#include "y/ink/image/formats.hpp"
#include "y/utest/run.hpp"

#include "y/ink/filter/prewitt3.hpp"
#include "y/ink/filter/prewitt5.hpp"

using namespace Yttrium;
using namespace Ink;

#include "y/color/x11.hpp"
#include "y/concurrent/api/simd/crew.hpp"
#include "y/color/conversion.hpp"

namespace
{
    static const Color::RGBA32 table[] = { Y_Black, Y_Orange, Y_White };

}

namespace
{
    template <typename FILTER>
    static void process(Broker &broker, Gradient<float> &g, const Pixmap<float> &gsf )
    {
        const String        name = FILTER::Label;
        const Color::Ramp   ramp(Y_Color_Ramp_From(table));
        const Filter<float> F( Y_Ink_Filter_From(FILTER) );
        std::cerr << "Using " << name << std::endl;
        FilterGradient<float>::Compute(broker,g,F,gsf);

    }
}

Y_UTEST(grad)
{
    Concurrent::Processor cpus = new Concurrent::Crew( Concurrent::Site::Default );
    Ink::Broker           broker(cpus);
    Formats &             IMG = Formats::Std();

    if(argc>1)
    {
        Image           img = IMG.load(argv[1],0);
        Pixmap<float>   gsf(img.w,img.h);

        Ops::Convert(broker,gsf,Color::Convert::RGBATo<float>, img);
        std::cerr << "Saving sources" << std::endl;
        IMG.save(img,"img.png",0);
        IMG.save(broker,Color::Convert::ToRGBA<float>,gsf, "gsf.png", 0);

        std::cerr << "computing..." << std::endl;
        Gradient<float> g(img.w,img.h);
        process<Prewitt3>(broker,g,gsf);
        process<Prewitt5>(broker,g,gsf);


        //IMG.save(ramp2,broker,g, "gsf-grad.png", 0);

    }


}
Y_UDONE()
