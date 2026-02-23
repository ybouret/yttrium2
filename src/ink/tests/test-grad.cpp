
#include "y/ink/filter/gradient.hpp"
#include "y/ink/image/formats.hpp"
#include "y/utest/run.hpp"

namespace Yttrium
{
    namespace Ink
    {



        template <typename T>
        struct FilterGradient
        {
            typedef V2D<T> vtx_t;

            template <typename SCALAR> static inline
            void Compute(Broker               & broker,
                         Pixmap<T>            & amplitude,
                         Pixmap<vtx_t>        & direction,
                         const Filter<T>      & filter,
                         const Pixmap<SCALAR> & source)
            {
                broker.prep(amplitude);
                broker.run(Run<SCALAR>,amplitude,direction,filter,source);
            }

        private:
            template <typename SCALAR> static inline
            void Run(Lockable             &,
                     const Tile           & tile,
                     Pixmap<T>            & amplitude,
                     Pixmap<vtx_t>        & direction,
                     const Filter<T>      & filter,
                     const Pixmap<SCALAR> & source)
            {
                for(unit_t j=tile.h;j>0;--j)
                {
                    const Segment s = tile[j];
                    Point         p = s.start;
                    for(unit_t i=s.width;i>0;--i,++p.x)
                        filter.loadGradient(amplitude,direction,source,p);
                }
            }

        };



    }

}


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

    static const int8_t f[3][3] =
    {
        {  -1,  -1,  -1 },
        {   0,  0,    0 },
        {   1,  1,    1 }
    };

    Filter<float> F( &f[0][0], sizeof(f)/sizeof(f[0][0]));
    std::cerr << F << std::endl;

    Formats &IMG = Formats::Std();
    if(argc>1)
    {
        Image           img = IMG.load(argv[1],0);
        Pixmap<float>   gsf(img.w,img.h);

        Ops::Convert(broker,gsf,Color::Convert::RGBATo<float>,  img);



        typedef V2D<float> vtx_t;
        Pixmap<float> g(img.w,img.h);
        Pixmap<vtx_t> gv(img.w,img.h);

        FilterGradient<float>::Compute(broker,g,gv,F,gsf);

        std::cerr << "Saving..." << std::endl;
        IMG.save(img,"img.png",0);
        IMG.save(broker,Color::Convert::ToRGBA<float>,gsf, "gsf.png", 0);
        IMG.save(ramp2,broker,g, "gsf-grad.png", 0);
        
    }


}
Y_UDONE()
