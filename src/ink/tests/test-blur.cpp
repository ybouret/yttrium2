
#include "y/ink/blur.hpp"

#include "y/ink/blur/lorentz.hpp"
#include "y/ink/blur/gauss.hpp"

#include "y/utest/run.hpp"
#include "y/core/utils.hpp"

#include "y/ink/ops.hpp"
#include <cstring>

#include "y/ink/image/formats.hpp"



namespace Yttrium
{
    namespace Ink
    {
        
        
        

        template <typename U>
        struct BlurProcess
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
                BlurProcess<U>::template Apply<BLUR>(broker,target,blur,source);
            }
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

inline uint8_t RGBA2GSU(const RGBA &c)
{
    return Color::Gray::To<uint8_t>::Get(c.r,c.g,c.b);
}

inline void rgba2gsu(void * const u, const void * const c)
{
    *(uint8_t *)u = RGBA2GSU( *(const RGBA *)c );
}

static inline RGBA GSU2RGBA(const float u)
{
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

        IMG.save(img,"img.png",0);

        {
            Pixmap<float> pxm(CopyOf,img,rgba2gsf);
            Pixmap<float> out(img.w,img.h);


            Ops::Convert(broker,tgt,GSF2RGBA,pxm);
            IMG.save(tgt, "gsf.png", 0);

            BlurFilter:: Apply(broker,out,gauss,pxm);
            Ops::Convert(broker,tgt,GSF2RGBA,out);
            IMG.save(tgt, "gsf-blur.png", 0);
        }

        {
            Pixmap<uint8_t> pxm(CopyOf,img,rgba2gsu);
            Pixmap<uint8_t> out(img.w,img.h);

            Ops::Convert(broker,tgt,GSU2RGBA,pxm);
            IMG.save(tgt, "gsu.png", 0);

            BlurFilter:: Apply(broker,out,gauss,pxm);
            Ops::Convert(broker,tgt,GSU2RGBA,out);
            IMG.save(tgt, "gsu-blur.png", 0);
        }

        BlurFilter:: Apply(broker,tgt,gauss,img);
        IMG.save(tgt,"img-blur.png",0);

    }




}
Y_UDONE()

