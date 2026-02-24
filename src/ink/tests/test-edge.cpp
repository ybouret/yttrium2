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

        struct LocalMaxima
        {
            static const uint8_t Feeble = 127;
            static const uint8_t Strong = 255;

            template <typename T> static inline
            void Keep(Broker &broker, Histogram &H, Pixmap<uint8_t> &edge, Pixmap<T> &thin, const Gradient<T> &g)
            {
                assert( Ops::HaveSameArea(thin,g) );
                assert( Ops::HaveSameArea(edge,g) );

                // first pass: keep only local maxima
                broker.prep(thin);
                broker.acquireLocalMemory( Histogram::LocalMemory );
                broker.run(Thin<T>,thin,g);
                const T gmax = GMax<T>(broker); std::cerr << "gmax=" << gmax << std::endl;

                // second pass: build quantized edge and its histogram
                broker.run(Hist<T>,edge,thin,gmax);

                // build histogram and threshold
                H.ldz();
                for(size_t i=broker.size();i>0;--i)
                {
                    const Tile &tile = broker[i]; if(tile.isEmpty()) break;
                    H += static_cast<const Histogram::Type *>( tile.entry );
                }
                const uint8_t threshold = Otsu::Threshold(H);
                std::cerr << "threshold=" << (int)threshold << std::endl;

                // part strong from feeble
                broker.run(Part,edge,threshold);
            }

        private:
            template <typename T> static inline
            T GMax(const Broker &broker)
            {
                size_t i = broker.size(); assert(i>0); assert( !broker[i].isEmpty() );
                T gmax = broker[i].as<T>();
                for(--i;i>0;--i)
                {
                    const Tile &tile = broker[i]; if(tile.isEmpty()) break;
                    InSituMax(gmax,tile.as<T>());
                }
                return gmax;
            }

            static
            void Part(Lockable &,
                      const Tile      &tile,
                      Pixmap<uint8_t> &edge,
                      const uint8_t    threshold) noexcept
            {
                const uint8_t discarded = threshold >> 1;
                for(unit_t j=tile.h;j>0;--j)
                {
                    const Segment         s = tile[j];
                    Pixmap<uint8_t>::Row &u = edge[s.start.y];
                    for(unit_t i=s.width,x=s.start.x;i>0;--i,++x)
                    {
                        uint8_t &b = u[x];
                        if(b<=discarded) { b=0;      continue; }
                        if(b<=threshold) { b=Feeble; continue; }
                        b = Strong;
                    }
                }
            }


            template <typename T> static inline
            void Hist(Lockable &,
                      Tile &           tile,
                      Pixmap<uint8_t> &edge,
                      const Pixmap<T> &thin,
                      const T          gmax)
            {
                const T zero(0);
                const T bmax(255);
                const T half(0.5);


                assert(tile.bytes>=Histogram::LocalMemory);
                Histogram::Type * const H = static_cast<Histogram::Type * const>(tile.entry);
                memset(H,0,Histogram::LocalMemory);

                for(unit_t j=tile.h;j>0;--j)
                {
                    const Segment                   s   = tile[j];
                    Pixmap<uint8_t>::Row &          tgt = edge[s.start.y];
                    const typename Pixmap<T>::Row & src = thin[s.start.y];
                    for(unit_t i=s.width,x=s.start.x;i>0;--i,++x)
                    {
                        const T g = src[x];
                        if(g>zero) {
                            const uint8_t b = (uint8_t) floor(half + (bmax*g)/gmax );
                            if(b>0)
                                ++H[tgt[x] = b];
                        }
                        else
                        {
                            tgt[x] = 0;
                        }
                    }
                }
            }

            template <typename T> static inline
            void Thin(Lockable          &,
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
        Pixmap<uint8_t> edge(img.w,img.h);

        Ops::Convert(broker,gsf,Color::Convert::RGBATo<float>, img);
        FilterGradient<float>::Compute(broker,g,F,gsf);
        IMG.save(img,"img.png",0);
        IMG.save(broker,Color::Convert::ToRGBA<float>,gsf, "gsf.png", 0);
        IMG.save(ramp,broker,g,"gsf-grad.png", 0);

        Histogram H;
        LocalMaxima::Keep(broker,H,edge,thin,g);
        IMG.save(ramp, broker,thin,"gsf-thin.png", 0);
        IMG.save(ramp2,broker,edge,"gsf-edge.png", 0);
        H.save("hist.dat");

    }
}
Y_UDONE()
