#include "y/ink/edge/blobs.hpp"
#include "y/ink/edge/local-maxima.hpp"
#include "y/ink/edge/double-threshold.hpp"

#include "y/ink/filter/gradient.hpp"
#include "y/ink/image/formats.hpp"
#include "y/utest/run.hpp"

#include "y/concurrent/api/simd/crew.hpp"
#include "y/color/x11.hpp"
#include "y/color/conversion.hpp"

#include "y/ink/filter/scharr5.hpp"
#include "y/ink/histogram/otsu.hpp"
#include <cstring>


#include "y/protean/coop/heavy/list.hpp"

namespace Yttrium
{
    namespace Ink
    {

        typedef Protean::CoopHeavyList<Point,MultiThreadedObject> ParticleList;
        typedef ParticleList::PoolType                            ParticlePool;

        class Particle : public Object, public ParticleList
        {
        public:
            explicit Particle(const ParticlePool &pool) :
            Object(),
            ParticleList(pool),
            kind(0),
            next(0),
            prev(0)
            {}
            
            virtual ~Particle() noexcept {}

            uint8_t    kind;
            Particle * next;
            Particle * prev;

        private:
            Y_Disable_Copy_And_Assign(Particle);
        };



        DoubleThreshold OtsuAndHalf(const Histogram &H) noexcept
        {
            const uint8_t strong = Otsu::Threshold(H);
            return DoubleThreshold(strong>>1,strong);
        }

        template <Histogram::Quartile Q>
        DoubleThreshold OtsuAndQuartile(const Histogram &H) noexcept
        {
            const uint8_t strong = Otsu::Threshold(H);
            const uint8_t feeble = H.find(Q,0,strong);
            return DoubleThreshold(feeble,strong);
        }



    }
}


#include "y/ink/ops/ld.hpp"
#include "y/container/sequence/vector.hpp"




using namespace Yttrium;
using namespace Ink;

namespace
{
    static const Color::RGBA32 table[]  = { Y_Black, Y_Red, Y_White };
    static const Color::RGBA32 table2[] = { Y_Black, Y_Magenta, Y_White };

}

#include "y/container/algorithm/disperse.hpp"

static inline double DeltaColor(const Color::RGBA32 &lhs, const Color::RGBA32 &rhs)
{
    const double dr = (double)lhs.r - (double)rhs.r;
    const double dg = (double)lhs.g - (double)rhs.g;
    const double db = (double)lhs.b - (double)rhs.b;
    return sqrt(dr*dr+dg*dg+db*db);
}

Y_UTEST(edge)
{
    Concurrent::Processor cpus = new Concurrent::Crew( Concurrent::Site::Default );
    Ink::Broker           broker(cpus);
    Formats &             IMG  = Formats::Std();
    const Filter<float>   F(     Y_Ink_Filter_From(Scharr5) );
    const Color::Ramp     ramp(  Y_Color_Ramp_From(table)   );
    const Color::Ramp     ramp2( Y_Color_Ramp_From(table2)  );

    Ink::ParticlePool pool;

    Ink::Particle pt(pool);
    pt.free();



    Y_PRINTV(Color::X11::Count);
    Vector<RGBA> x11map;
    {
        Histogram    intensity;
        for(size_t i=0;i<Color::X11::Count;++i)
        {
            const Color::X11 & x11  = Color::X11::Table[i];
            const uint8_t      I    = Color::Conv::GrayScale<uint8_t>::From(x11.r,x11.g,x11.b);
            //std::cerr << std::setw(24) << x11.name << " : I=" << (int)I << std::endl;
            ++intensity[I];
            if(I>=128)
            {
                x11map << RGBA(x11.r,x11.g,x11.b);
            }
        }

        intensity.toCDF();
        intensity.save("x11hist.dat");
        std::cerr << "#x11map=" << x11map.size() << std::endl;
    }
    Vector<size_t> x11idx(x11map.size(),0);

    Algo::Disperse::With<double>::Make(x11idx, DeltaColor, x11map);

    Vector<RGBA> icol;
    for(size_t i=1;i<=x11idx.size();++i)
    {
        icol << x11map[ x11idx[i] ];
    }

    if(argc>1)
    {
        const Image     img = IMG.load(argv[1],0);
        Pixmap<float>   gsf(img.w,img.h);
        Gradient<float> g(img.w,img.h);
        Pixmap<float>   thin(img.w,img.h);
        Pixmap<uint8_t> edge0(img.w,img.h);
        Pixmap<uint8_t> edge2(img.w,img.h);
        Pixmap<uint8_t> edge3(img.w,img.h);
        Pixmap<size_t>  blob(img.w,img.h);


        Ops::Convert(broker,gsf,Color::Convert::RGBATo<float>, img);
        FilterGradient<float>::Compute(broker,g,F,gsf);
        IMG.save(img,"img.png",0);
        IMG.save(broker,Color::Convert::ToRGBA<float>,gsf, "gsf.png", 0);
        IMG.save(ramp,broker,g,"gsf-grad.png", 0);

        Histogram H;
        LocalMaxima::Keep(broker,H,edge0,thin,g);
        IMG.save(ramp, broker,thin,"gsf-thin.png", 0);
        H.save("hist.dat");
        Ops::Copy(broker,edge2,edge0);
        Ops::Copy(broker,edge3,edge0);

        const DoubleThreshold part0 = OtsuAndHalf(H);
        std::cerr << "part0=" << part0 << std::endl;
        LocalMaxima::Part(broker,edge0,part0);
        IMG.save(ramp2,broker,edge2,"gsf-edge0.png", 0);


        const DoubleThreshold part2 = OtsuAndQuartile<Histogram::Q2>(H);
        std::cerr << "part2=" << part2 << std::endl;
        LocalMaxima::Part(broker,edge2,part2);
        IMG.save(ramp2,broker,edge2,"gsf-edge2.png", 0);

        const DoubleThreshold part3 = OtsuAndQuartile<Histogram::Q3>(H);
        std::cerr << "part3=" << part3 << std::endl;
        LocalMaxima::Part(broker,edge3,part3);
        IMG.save(ramp2,broker,edge3,"gsf-edge3.png", 0);


        Blobs blobs(img.w,img.h);

        blobs.build(broker,edge0);
        IMG.save(icol, broker,blobs,"gsf-blobs0.png", 0);

        blobs.build(broker,edge2);
        IMG.save(icol, broker,blobs,"gsf-blobs2.png", 0);

        blobs.build(broker,edge3);
        IMG.save(icol, broker,blobs,"gsf-blobs3.png", 0);
    }
}
Y_UDONE()
