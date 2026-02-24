#include "y/ink/filter/gradient.hpp"
#include "y/ink/image/formats.hpp"
#include "y/utest/run.hpp"

#include "y/concurrent/api/simd/crew.hpp"
#include "y/color/x11.hpp"
#include "y/color/conversion.hpp"

#include "y/ink/filter/scharr5.hpp"

namespace Yttrium
{
    namespace Ink
    {

        struct LocalMaxima
        {

            template <typename T> static inline
            void Keep(Broker &broker, Pixmap<T> &thin, const Gradient<T> &g)
            {
                assert( Ops::HaveSameArea(thin,g) );
                broker.prep(thin);
                broker.acquireLocalMemory( sizeof(T) );
                broker.run(Run<T>,thin,g);
            }

            template <typename T> static inline
            void Run(Lockable          &,
                     Tile              &tile,
                     Pixmap<T>         &thin,
                     const Gradient<T> &g)
            {
                const T half(0.5);
                const T zero(0);
                T &     gmax = (tile.as<T>() = zero);
                for(unit_t j=tile.h;j>0;--j)
                {
                    const Segment                       s   = tile[j];
                    Point                               p   = s.start;
                    typename Pixmap<T>::Row            &tgt = thin[p.y];
                    const typename Pixmap<T>::Row      &src = g[p.y];
                    const typename Pixmap<V2D<T>>::Row &vec = g.dir[p.y];
                    for(unit_t i=s.width;i>0;--i,++p.x)
                    {
                        const T      g0 = src[p.x];
                        const V2D<T> v0 = vec[p.x];
                        const Point  dv( (unit_t) floor(v0.x+half), (unit_t) floor(v0.y+half) );
                        const T      gp = g[p+dv];
                        const T      gm = g[p-dv];
                        if(g0>=gp&&g0>=gm)
                        {
                            InSituMax(gmax,tgt[p.x] = g0);
                        }
                        else
                        {
                            tgt[p.x] = zero;
                        }
                    }
                }
            }

        };

    }
}
using namespace Yttrium;
using namespace Ink;

namespace
{
    static const Color::RGBA32 table[] = { Y_Black, Y_Red, Y_White };
}

Y_UTEST(edge)
{
    Concurrent::Processor cpus = new Concurrent::Crew( Concurrent::Site::Default );
    Ink::Broker           broker(cpus);
    Formats &             IMG  = Formats::Std();
    const Filter<float>   F( Y_Ink_Filter_From(Scharr5) );
    const Color::Ramp     ramp( Y_Color_Ramp_From(table) );
    if(argc>1)
    {
        const Image     img = IMG.load(argv[1],0);
        Pixmap<float>   gsf(img.w,img.h);
        Gradient<float> g(img.w,img.h);
        Pixmap<float>   thin(img.w,img.h);

        Ops::Convert(broker,gsf,Color::Convert::RGBATo<float>, img);
        FilterGradient<float>::Compute(broker,g,F,gsf);
        IMG.save(img,"img.png",0);
        IMG.save(broker,Color::Convert::ToRGBA<float>,gsf, "gsf.png", 0);
        IMG.save(ramp,broker,g,"gsf-grad.png", 0);

        LocalMaxima::Keep(broker,thin,g);
        IMG.save(ramp,broker,thin,"gsf-thin.png", 0);

    }
}
Y_UDONE()
