#include "y/ink/edge/local-maxima.hpp"
#include <cstring>

namespace Yttrium
{
    namespace Ink
    {

        namespace
        {
            static inline
            void Thinning(Lockable              &,
                          Tile                  &tile,
                          Pixmap<float>         &thin,
                          const Gradient<float> &grad)
            {
                float & gmax = (tile.as<float>() = 0.0f);
                for(unit_t j=tile.h;j>0;--j)
                {
                    const Segment                    s   = tile[j];
                    Point                            p   = s.start;
                    Pixmap<float>::Row             & tgt = thin[p.y];
                    const Pixmap<float>::Row       & src = grad[p.y];
                    const  Pixmap<V2D<float>>::Row & vec = grad.dir[p.y];
                    for(unit_t i=s.width;i>0;--i,++p.x)
                    {
                        const float      g0 = src[p.x]; if(g0<=0.0f) { tgt[p.x] = 0.0f; continue; }
                        const V2D<float> v0 = vec[p.x];
                        const Point      dv( (unit_t) floorf(v0.x+0.5f), (unit_t) floorf(v0.y+0.5f) );
                        const float      gp = grad[p+dv];
                        const float      gm = grad[p-dv];
                        if(g0>=gp&&g0>=gm)
                        {
                            InSituMax(gmax,tgt[p.x] = g0);
                        }
                        else
                        {
                            tgt[p.x] = 0.0f;
                        }
                    }
                }
            }

            static inline
            float MaxGradient(const Broker &broker)
            {
                size_t i = broker.size(); assert(i>0); assert( !broker[i].isEmpty() );
                float gmax = broker[i].as<float>();
                for(--i;i>0;--i)
                {
                    const Tile &tile = broker[i]; if(tile.isEmpty()) break;
                    InSituMax(gmax,tile.as<float>());
                }
                return gmax;
            }


            static inline
            void Quantize(Lockable &,
                          Tile                & tile,
                          Pixmap<uint8_t>     & edge,
                          const Pixmap<float> & thin,
                          const float           gmax)
            {


                assert(tile.bytes>=Histogram::LocalMemory);
                Histogram::Type * const H = static_cast<Histogram::Type *>(tile.entry);
                memset(H,0,Histogram::LocalMemory);

                for(unit_t j=tile.h;j>0;--j)
                {
                    const Segment              s   = tile[j];
                    Pixmap<uint8_t>::Row     & tgt = edge[s.start.y];
                    const Pixmap<float>::Row & src = thin[s.start.y];
                    for(unit_t i=s.width,x=s.start.x;i>0;--i,++x)
                    {
                        const float g = src[x];
                        if(g>0.0f) {
                            const uint8_t b = (uint8_t) floorf(0.5f + (255.0f*g)/gmax );
                            if(b>0)
                                ++H[ tgt[x]=b ];
                        }
                        else
                            tgt[x] = 0;
                    }
                }
            }
        }


        void LocalMaxima:: Keep(Broker &broker, Histogram &hist, Pixmap<uint8_t> &edge, Pixmap<float> &thin, const Gradient<float> &grad)
        {
            assert( Ops::HaveSameArea(thin,grad) );
            assert( Ops::HaveSameArea(edge,grad) );

            // first pass: apply thinning and collect gmax
            broker.prep(thin);
            broker.acquireLocalMemory( Histogram::LocalMemory );
            broker.run(Thinning,thin,grad);
            const float gmax = MaxGradient(broker);  

            // second pass: build quantized edge and its histogram
            broker.run(Quantize,edge,thin,gmax);
            hist.ldz();
            for(size_t i=broker.size();i>0;--i)
            {
                const Tile &tile = broker[i]; if(tile.isEmpty()) break;
                hist += static_cast<const Histogram::Type *>( tile.entry );
            }
        }

    }

}


