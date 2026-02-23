#include "y/ink/image/formats.hpp"
#include "y/utest/run.hpp"

#include "y/ink/filter.hpp"





namespace Yttrium
{
    namespace Ink
    {

        template <typename T, typename SCALAR>
        struct FilterImmediateOn
        {
            const Filter<T> & filter;
            inline void operator()(Pixmap<T> &target, const Pixmap<SCALAR> &source, const Point origin)
            {
                filter.template loadImmediate<SCALAR,SCALAR,1>(&target[origin],source,origin);
            }
        };

        template <typename T, typename SCALAR>
        struct FilterTransposeOn
        {
            const Filter<T> & filter;
            inline void operator()(Pixmap<T> &target, const Pixmap<SCALAR> &source, const Point origin)
            {
                filter.template loadTranspose<SCALAR,SCALAR,1>(&target[origin],source,origin);
            }
        };

        template <typename T>
        struct FilterProcess
        {
            template <typename SCALAR> static inline
            void ImmediateOn(Broker &broker, Pixmap<T> &target, const Filter<T> &filter, const Pixmap<SCALAR> &source)
            {
                FilterImmediateOn<T,SCALAR> F = { filter };
                Ops::Transform(broker,target,F,source);
            }

            template <typename SCALAR> static inline
            void TransposeOn(Broker &broker, Pixmap<T> &target, const Filter<T> &filter, const Pixmap<SCALAR> &source)
            {
                FilterTransposeOn<T,SCALAR> F = { filter };
                Ops::Transform(broker,target,F,source);
            }
        };

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
    static const Color::RGBA32 table2[] = { Y_Black, Y_Blue, Y_Green, Y_Red };
}

Y_UTEST(filter)
{
    Concurrent::Processor cpus = new Concurrent::Crew( Concurrent::Site::Default );
    Ink::Broker           broker(cpus);
    const Color::Ramp     ramp("ramp",table,sizeof(table)/sizeof(table[0]));
    const Color::Ramp     ramp2("ramp2",table,sizeof(table2)/sizeof(table2[0]));

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

        typedef V2D<float> vtx_t;
        Pixmap<float> g(img.w,img.h);
        Pixmap<vtx_t> gv(img.w,img.h);
        
        FilterGradient<float>::Compute(broker,g,gv,F,gsf);
        IMG.save(ramp2,broker,g, "gsf-grad.png", 0);



    }

}
Y_UDONE()
