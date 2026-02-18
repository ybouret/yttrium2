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
        class BlurData : public BlurMetrics, public CxxSeries< FilterElement<T> >
        {
        public:
            typedef FilterElement<T>   Element;
            typedef CxxSeries<Element> Elements;
            typedef TypeToType<T>      MyTypeHint;

            template <typename PROC>
            explicit BlurData(PROC &proc, const unit_t rmax) :
            BlurMetrics(rmax),
            Elements(count()),
            denom(0)
            {
                Elements           & self = *this;
                Cameo::Addition<T>   add;
                const T              f0 = proc(0);
                for(unit_t y=-r;y<=r;++y)
                {
                    const unit_t y2 = y*y;
                    for(unit_t x=-r;x<=r;++x)
                    {
                        const unit_t ir2 = x*x+y2;
                        if(ir2<=r2)
                        {
                            const Point p(x,y);
                            const T     w = proc( ir2 )/f0;
                            if(w<=denom) throw Specific::Exception("Blur", "invalid weight");
                            add << w;
                            self.push(p,w);
                        }
                    }
                }
                Coerce(denom) = add.sum();
                Sorting::Heap::Sort(self,Element::Compare);
            }

            //! compute result in T values
            template <
            typename       PIXEL,
            typename       PTYPE,
            const unsigned NCHAN
            >
            void load(T * const            target,
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


            virtual ~BlurData() noexcept
            {
            }

            void apply(Pixmap<T>       &target,
                       const Pixmap<T> &source,
                       const Point      origin)
            {
                // put direct result
                load<T,T,1>(&target[origin],source,origin);
            }

            void apply(Pixmap<uint8_t>       &target,
                       const Pixmap<uint8_t> &source,
                       const Point            origin)
            {
                // get result in T tpe
                T res = 0; load<uint8_t,uint8_t,1>(&res,source,origin);

                // convert to byte
                target[origin] = Color::Gray::UnitToByte(res);
            }


            const T       denom;


        private:
            Y_Disable_Copy_And_Assign(BlurData);

        };

        template <typename T> class BlurFunction
        {
        public:
            inline explicit BlurFunction() noexcept : one(1) {}
            inline virtual ~BlurFunction() noexcept {}

            virtual T operator()(const unit_t r2) const = 0;

            inline const BlurFunction & blurFunction() const noexcept { return *this; }

            inline unit_t rmax() const
            {
                const T       Dmax = 256;
                const T       Vmin = one/Dmax;
                const BlurFunction &F  = *this;
                const T       f0 = F(0);
                for(unit_t r=1;;++r)
                {
                    const T f = F(r*r);
                    if(f/f0<=Vmin)
                        return --r;
                }
            }

            const T one; //!< 1

        private:
            Y_Disable_Copy_And_Assign(BlurFunction);
        };


        template <typename T>
        class BlurHook : public BlurData<T>
        {
        public:
            inline explicit BlurHook(const BlurFunction<T> &F) :
            BlurData<T>(F,F.rmax())
            {
            }

            inline virtual ~BlurHook() noexcept
            {
            }


        private:
            Y_Disable_Copy_And_Assign(BlurHook);
        };

        template <typename T, template <typename> class FUNCTION>
        class Blur : public FUNCTION<T>, public BlurHook<T>
        {
        public:
            using FUNCTION<T>::blurFunction;

            inline explicit Blur() : FUNCTION<T>(), BlurHook<T>( blurFunction() )
            {
            }

            inline explicit Blur(const T arg1) : FUNCTION<T>(arg1), BlurHook<T>( blurFunction() )
            {
            }

            inline explicit Blur(const T arg1, const T arg2) : FUNCTION<T>(arg1,arg2), BlurHook<T>( blurFunction() )
            {
            }


            inline virtual ~Blur() noexcept {}


        private:
            Y_Disable_Copy_And_Assign(Blur);
        };

        template <typename U>
        struct BlurWrapper
        {
            template <typename BLUR> static inline
            void Apply(Broker &broker, Pixmap<U> &target, BLUR &blur, const Pixmap<U> &source)
            {
                App<BLUR> app(blur);
                Ops::Transform(broker,target,app,source);
            }

        private:
            template <typename BLUR>
            class App
            {
            public:
                inline explicit App(BLUR &_blur) noexcept : blur(_blur)
                {
                }

                inline virtual ~App() noexcept
                {
                }

                inline void operator()(Pixmap<U>       & target,
                                       const Pixmap<U> & source,
                                       const Point       origin)
                {
                    blur.apply(target,source,origin);
                }

            private:
                Y_Disable_Copy_And_Assign(App);
                BLUR &blur;
            };
        };


        struct BlurFilter
        {
            template <typename U, typename BLUR> static inline
            void Apply(Broker &broker, Pixmap<U> &target, BLUR &blur, const Pixmap<U> &source)
            {
                BlurWrapper<U>::template Apply<BLUR>(broker,target,blur,source);
            }
        };





        template <typename T>
        class GaussBlur : public BlurFunction<T>
        {
        public:
            inline explicit GaussBlur(const T stddev) :
            sig( stddev ),
            sig2( sig*sig ),
            denom( sig2+sig2 )
            {

            }

            inline virtual ~GaussBlur() noexcept {}

            virtual T operator()(const unit_t r2) const
            {
                const T u2 = (T)r2;
                const T arg = u2 / denom;
                return exp(-arg);
            }

            const T sig;
            const T sig2;
            const T denom;

        private:
            Y_Disable_Copy_And_Assign(GaussBlur);
        };

        template <typename T>
        class LorentzBlur : public BlurFunction<T>
        {
        public:
            using BlurFunction<T>::one;

            inline explicit LorentzBlur(const T stddev) :
            sig( stddev ),
            sig2( sig*sig )
            {

            }

            inline virtual ~LorentzBlur() noexcept {}

            virtual T operator()(const unit_t r2) const
            {
                const T u2  = (T)r2;
                const T arg = u2 / sig2;
                return one/(one+arg);
            }

            const T sig;
            const T sig2;

        private:
            Y_Disable_Copy_And_Assign(LorentzBlur);
        };






    }
}


using namespace Yttrium;
using namespace Ink;

#include "y/concurrent/api/simd/crew.hpp"

inline float RGBA2GSF(const RGBA &c)
{
    return Color::Gray::To<float>::Get(c.r,c.g,c.b);
}

inline void rgba2gsf(void * const f, const void * const c)
{
    *(float *)f = RGBA2GSF( *(const RGBA *)c );
}


static inline RGBA GSF2RGBA(const float f)
{
    const unit_t u = Color::Gray::UnitToByte(f);
    return RGBA(u,u,u);
}



Y_UTEST(blur)
{

    for(float s=0.1f;s<=10.0f;s+=0.1f)
    {
        std::cerr << "sigma=" << std::setw(8) << s << " :";
        GaussBlur<float>    G(s);  std::cerr << " gauss.rmax=" << G.rmax();
        LorentzBlur<float>  L(s);  std::cerr << " lorentz.rmax=" << L.rmax();
        std::cerr << std::endl;
    }

    Concurrent::Processor cpus = new Concurrent::Crew( Concurrent::Site::Default );
    Ink::Broker           broker(cpus);
    Formats     &IMG = Formats::Std();

    Blur<float,GaussBlur> gauss(2.7f);


    if(argc>1)
    {
        Image         img = IMG.load(argv[1],0);
        Image         tgt(img.w,img.h);
        Pixmap<float> pxm(CopyOf,img,rgba2gsf);
        Pixmap<float> out(img.w,img.h);

        Ops::Convert(broker,tgt,GSF2RGBA,pxm);
        IMG.save(tgt, "gs.png", 0);

        BlurFilter:: Apply(broker,out,gauss,pxm);
        Ops::Convert(broker,tgt,GSF2RGBA,out);
        IMG.save(tgt, "gs-blur.png", 0);

    }




}
Y_UDONE()

