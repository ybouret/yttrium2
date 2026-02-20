#include "y/ink/image/formats.hpp"
#include "y/utest/run.hpp"

#include "y/ink/filter.hpp"





namespace Yttrium
{
    namespace Ink
    {

       

        template <typename SCALAR>
        struct ApplyFilter
        {
            template <typename T> static inline
            void Fill(T                    & target,
                      Filter<T>            & filter,
                      const Pixmap<SCALAR> & source,
                      const Point            point)
            {
                filter.template loadImmediate<SCALAR,SCALAR,1>(&target,source,point);
            }
        };


    }

}

#include "y/ink/image/formats.hpp"
#include "y/color/conversion.hpp"
#include "y/concurrent/api/simd/crew.hpp"

using namespace Yttrium;
using namespace Ink;

Y_UTEST(filter)
{
    Concurrent::Processor cpus = new Concurrent::Crew( Concurrent::Site::Default );
    Ink::Broker           broker(cpus);

    static const int8_t f[3][3] =
    {
        { 1, 2, 3 },
        { 4, 5 ,6 },
        { 7, 8, 9 }
    };

    Filter<float> F( &f[0][0], sizeof(f)/sizeof(f[0][0]), 4);
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
        

        F.applyImmediate(tgt,gsf,Point(0,0));



    }

}
Y_UDONE()
