#include "y/ink/edge/local-maxima.hpp"
#include "y/ink/edge/double-threshold.hpp"

#include "y/ink/filter/gradient.hpp"
#include "y/ink/image/formats.hpp"
#include "y/utest/run.hpp"

#include "y/concurrent/api/simd/crew.hpp"
#include "y/color/x11.hpp"
#include "y/color/conversion.hpp"

#include "y/ink/filter/scharr5.hpp"
#include "y/ink/histogram/otsu.hpp"
#include <cstring>


namespace Yttrium
{
    namespace Ink
    {
        
        DoubleThreshold OtsuAndHalf(const Histogram &H) noexcept
        {
            const uint8_t strong = Otsu::Threshold(H);
            return DoubleThreshold(strong/2,strong);
        }

        template <Histogram::Quartile Q>
        DoubleThreshold OtsuAndQuartile(const Histogram &H) noexcept
        {
            const uint8_t strong = Otsu::Threshold(H);
            const uint8_t feeble = H.find(Q,0,strong);
            return DoubleThreshold(feeble,strong);
        }



    }
}
using namespace Yttrium;
using namespace Ink;

namespace
{
    static const Color::RGBA32 table[]  = { Y_Black, Y_Red, Y_White };
    static const Color::RGBA32 table2[] = { Y_Black, Y_Magenta, Y_White };

}

Y_UTEST(edge)
{
    Concurrent::Processor cpus = new Concurrent::Crew( Concurrent::Site::Default );
    Ink::Broker           broker(cpus);
    Formats &             IMG  = Formats::Std();
    const Filter<float>   F( Y_Ink_Filter_From(Scharr5) );
    const Color::Ramp     ramp( Y_Color_Ramp_From(table) );
    const Color::Ramp     ramp2( Y_Color_Ramp_From(table2) );

    if(argc>1)
    {
        const Image     img = IMG.load(argv[1],0);
        Pixmap<float>   gsf(img.w,img.h);
        Gradient<float> g(img.w,img.h);
        Pixmap<float>   thin(img.w,img.h);
        Pixmap<uint8_t> edge0(img.w,img.h);
        Pixmap<uint8_t> edge2(img.w,img.h);
        Pixmap<uint8_t> edge3(img.w,img.h);

        Ops::Convert(broker,gsf,Color::Convert::RGBATo<float>, img);
        FilterGradient<float>::Compute(broker,g,F,gsf);
        IMG.save(img,"img.png",0);
        IMG.save(broker,Color::Convert::ToRGBA<float>,gsf, "gsf.png", 0);
        IMG.save(ramp,broker,g,"gsf-grad.png", 0);

        Histogram H;
        LocalMaxima::Keep(broker,H,edge0,thin,g);
        IMG.save(ramp, broker,thin,"gsf-thin.png", 0);
        H.save("hist.dat");
        Ops::Copy(broker,edge2,edge0);
        Ops::Copy(broker,edge3,edge0);

        const DoubleThreshold part0 = OtsuAndHalf(H);
        std::cerr << "part0=" << part0 << std::endl;
        LocalMaxima::Part(broker,edge0,part0);
        IMG.save(ramp2,broker,edge2,"gsf-edge0.png", 0);


        const DoubleThreshold part2 = OtsuAndQuartile<Histogram::Q2>(H);
        std::cerr << "part2=" << part2 << std::endl;
        LocalMaxima::Part(broker,edge2,part2);
        IMG.save(ramp2,broker,edge2,"gsf-edge2.png", 0);

        const DoubleThreshold part3 = OtsuAndQuartile<Histogram::Q3>(H);
        std::cerr << "part3=" << part3 << std::endl;
        LocalMaxima::Part(broker,edge3,part3);
        IMG.save(ramp2,broker,edge3,"gsf-edge3.png", 0);
    }
}
Y_UDONE()
