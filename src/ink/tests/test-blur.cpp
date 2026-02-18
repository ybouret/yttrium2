#include "y/utest/run.hpp"
#include "y/container/algorithm/unique.hpp"
#include "y/container/sequence/vector.hpp"
#include "y/sorting/heap.hpp"
#include "y/container/cxx/series.hpp"
#include "y/calculus/iabs.hpp"
#include "y/core/utils.hpp"
#include "y/cameo/addition.hpp"

#include "y/ink/ops/filter/element.hpp"
#include "y/ink/ops.hpp"
#include <cstring>

#include "y/ink/image/formats.hpp"



namespace Yttrium
{
    namespace Ink
    {

        class BlurMetrics
        {
        public:
            explicit BlurMetrics(const unit_t rmax);
            virtual ~BlurMetrics() noexcept;

            size_t count() const;

            const unit_t r;
            const unit_t r2;

        private:
            Y_Disable_Copy_And_Assign(BlurMetrics);
        };

        BlurMetrics:: BlurMetrics(const unit_t rmax) :
        r( IntegerAbs(rmax) ),
        r2(r*r)
        {
        }

        BlurMetrics:: ~BlurMetrics() noexcept
        {

        }


        size_t BlurMetrics:: count() const
        {
            size_t res = 0;
            for(unit_t y=-r;y<=r;++y)
            {
                const unit_t y2 = y*y;
                for(unit_t x=-r;x<=r;++x)
                {
                    if(x*x+y2<=r2) ++res;
                }
            }

            return res;
        }



        template <typename T>
        class Blur : public BlurMetrics, public CxxSeries< FilterElement<T> >
        {
        public:
            typedef FilterElement<T>   Element;
            typedef CxxSeries<Element> Elements;
            typedef TypeToType<T>      MyTypeHint;

            template <typename PROC>
            explicit Blur(PROC &proc, const unit_t rmax) :
            BlurMetrics(rmax),
            Elements(count()),
            denom(0)
            {
                Elements           & self = *this;
                Cameo::Addition<T>   add;
                for(unit_t y=-r;y<=r;++y)
                {
                    const unit_t y2 = y*y;
                    for(unit_t x=-r;x<=r;++x)
                    {
                        const unit_t ir2 = x*x+y2;
                        if(ir2<=r2)
                        {
                            const Point p(x,y);
                            const T     w = proc( (T)ir2 );
                            if(w<=denom) throw Specific::Exception("Blur", "invalid weight");
                            add << w;
                            self.push(p,w);
                        }
                    }
                }
                Coerce(denom) = add.sum();
                Sorting::Heap::Sort(self,Element::Compare);
            }

            template <
            typename       PIXEL,
            typename       PTYPE,
            const unsigned NCHAN
            >
            void load(PTYPE * const        target,
                      const Pixmap<PIXEL> &source,
                      const Point          origin)
            {
                {
                    const Elements &self = *this;
                    memset(target,0,sizeof(PTYPE)*NCHAN);
                    for(size_t i=self.size();i>0;--i)
                    {
                        static const MyTypeHint MyType = {};
                        const Element &         elem   = self[i];
                        const PTYPE * const     ptype  = (const PTYPE *) &source[origin+elem.p];
                        const T                 weight = elem.w;
                        for(size_t j=0;j<NCHAN;++j) {
                            target[j] += MKL::AdaptedTo(MyType,ptype[j]) * weight;
                        }
                    }
                }
                for(size_t j=0;j<NCHAN;++j) target[j] /= denom;
            }


            virtual ~Blur() noexcept
            {
            }

            void operator()(Pixmap<float>       &target,
                            const Pixmap<float> &source,
                            const Point          origin)
            {
                load<float,float,1>(&target[origin],source,origin);
            }


            const T       denom;


        private:
            Y_Disable_Copy_And_Assign(Blur);

        };

        float g(const float r2)
        {
            return expf(-r2/10.0f);
        }


    }
}


using namespace Yttrium;
using namespace Ink;

#include "y/concurrent/api/simd/crew.hpp"

inline float RGBA2GS(const RGBA &c)
{
    return Color::Gray::To<float>::Get(c.r,c.g,c.b);
}

inline void rgba2gs(void * const f, const void * const c)
{
    *(float *)f = RGBA2GS( *(const RGBA *)c );
}


static inline RGBA GS2RGBA(const float f)
{
    const unit_t u = Color::Gray::UnitToByte(f);
    return RGBA(u,u,u);
}



Y_UTEST(blur)
{
    Concurrent::Processor cpus = new Concurrent::Crew( Concurrent::Site::Default );
    Ink::Broker           broker(cpus);
    Formats     &IMG = Formats::Std();
    Blur<float> blur(Ink::g,5);
    std::cerr << "blur=" << blur << std::endl;
    
    if(argc>1)
    {
        Image         img = IMG.load(argv[1],0);
        Image         tgt(img.w,img.h);
        Pixmap<float> pxm(CopyOf,img,rgba2gs);

        Ops::Convert(broker,tgt,GS2RGBA,pxm);
        IMG.save(tgt, "gs.png", 0);

        
    }


}
Y_UDONE()

