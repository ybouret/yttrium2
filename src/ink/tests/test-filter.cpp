#include "y/ink/filter/process.hpp"

#include "y/ink/image/formats.hpp"
#include "y/utest/run.hpp"






#include "y/ink/image/formats.hpp"
#include "y/color/conversion.hpp"
#include "y/concurrent/api/simd/crew.hpp"
#include "y/ink/ops/getmax.hpp"
#include "y/ink/ops/getmin.hpp"
#include "y/color/ramp.hpp"
#include "y/color/x11.hpp"


using namespace Yttrium;
using namespace Ink;

namespace
{
    static const Color::RGBA32 table[]  = { Y_Blue, Y_Black, Y_Red };
    static const Color::RGBA32 table2[] = { Y_Black, Y_Orange, Y_White };

}

Y_UTEST(filter)
{
    Concurrent::Processor cpus = new Concurrent::Crew( Concurrent::Site::Default );
    Ink::Broker           broker(cpus);
    const Color::Ramp     ramp(Y_Color_Ramp_From(table));
    const Color::Ramp     ramp2(Y_Color_Ramp_From(table2));

    static const int8_t f[3][3] =
    {
        {   1,  1,   1 },
        {   0,  0,    0 },
        {   -1,  -1,    -1 }
    };

    Filter<float> F( &f[0][0], sizeof(f)/sizeof(f[0][0]));
    std::cerr << F << std::endl;

    Formats &IMG = Formats::Std();

    if(argc>1)
    {
        Image           img = IMG.load(argv[1],0);
        Pixmap<float>   gsf(img.w,img.h);
        Pixmap<uint8_t> gsu(img.w,img.h);
        Pixmap<float>   tgt(img.w,img.h);

        Ops::Convert(broker,gsf,Color::Convert::RGBATo<float>,  img);
        Ops::Convert(broker,gsu,Color::Convert::RGBATo<uint8_t>,img);

        IMG.save(img,"img.png",0);
        IMG.save(broker,Color::Convert::ToRGBA<float>,gsf, "gsf.png", 0);



        {
            FilterProcess<float>::ImmediateOn(broker,tgt,F,gsf);
            const float vmin = GetMin::Of(broker,tgt);
            const float vmax = GetMax::Of(broker,tgt);
            std::cerr << "vmin=" << vmin << ", vmax=" << vmax << std::endl;
            Color::RampOf<float> rmp(ramp,vmin,vmax);
            IMG.save(broker,rmp,tgt, "gsf-immediate.png", 0);
        }

        {
            FilterProcess<float>::TransposeOn(broker,tgt,F,gsf);
            const float vmin = GetMin::Of(broker,tgt);
            const float vmax = GetMax::Of(broker,tgt);
            std::cerr << "vmin=" << vmin << ", vmax=" << vmax << std::endl;
            Color::RampOf<float> rmp(ramp,vmin,vmax);
            IMG.save(broker,rmp,tgt, "gsf-transpose.png", 0);
        }



    }

}
Y_UDONE()
