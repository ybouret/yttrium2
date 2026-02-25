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


namespace Yttrium
{
    namespace Ink
    {

        DoubleThreshold OtsuAndHalf(const Histogram &H) noexcept
        {
            const uint8_t strong = Otsu::Threshold(H);
            return DoubleThreshold(strong/2,strong);
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
#include "y/protean/coop/heavy/list.hpp"
#include "y/container/sequence/vector.hpp"

namespace Yttrium
{
    namespace Ink
    {

        typedef Pixmap<size_t> IndexMap;

        class Blobs : public IndexMap
        {
        public:
            static const size_t Zero = 0;
            static const unit_t Delta[8][2];


            explicit Blobs(const size_t W, const size_t H) :
            IndexMap(W,H)
            {
            }

            virtual ~Blobs() noexcept {}


            void build(Broker &broker, Pixmap<uint8_t> &edge)
            {
                static const Point * const delta = Memory::Stealth::Cast<Point>( &Delta[0][0] );
                const size_t ncof = 8;
                IndexMap &   self = *this;
                assert(Ops::HaveSameArea(self,edge));
                LoadPixel::Set(broker,*this,Zero);
                size_t indx = 0;
                for(unit_t y=lower.y;y<=upper.y;++y)
                {
                    const Pixmap<uint8_t>::Row & erow = edge[y];
                    IndexMap::Row              & irow = (*this)[y];
                    for(unit_t x=lower.x;x<=upper.x;++x)
                    {
                        const uint8_t eval = erow[x];
                        if(eval<=0)   continue; // no edge
                        if(irow[x]>0) continue; // already detected

                        // start new blob
                        ++indx; stack.free();
                        stack << Point(x,y);
                        while( stack.size() > 0 )
                        {
                            const Point p = stack.pullTail();
                            if(0!=self[p]) { assert(indx==self[p]); continue; }
                            self[p] = indx;
                            for(size_t i=0;i<ncof;++i)
                            {
                                const Point q = p + delta[i];
                                if(!self.contains(q)) continue;
                                if(0==edge[q])        continue;
                                if(0!=self[q])        continue;
                                stack << q;
                            }
                        }
                    }
                }

                std::cerr << "indx=" << indx << std::endl;

            }

            Vector<Point> stack;


        private:
            Y_Disable_Copy_And_Assign(Blobs);
        };

        const unit_t Blobs:: Delta[8][2] =
        {
            // axis
            {  1,  0 },
            {  0,  1 },
            { -1,  0 },
            {  0, -1 },
            // diag
            {  1,  1 },
            { -1,  1 },
            { -1, -1 },
            {  1, -1 }
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

#include "y/calculus/prime/next.hpp"
#include "y/calculus/prime/prev.hpp"

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
        PixelRange<size_t> px = MinMax::Of(broker,blobs);
        std::cerr << px.vmin << ":" << px.vmax  << std::endl;
        Vector<RGBA> icol(WithAtLeast,px.vmax+1);
        icol << Y_Black;

        Y_PRINTV(Color::X11::Count);
        Y_PRINTV(Prime::Prev(Color::X11::Count));

        Vector<RGBA> x11map;
        Histogram    intensity;
        for(size_t i=0;i<Color::X11::Count;++i)
        {
            const Color::X11 & x11  = Color::X11::Table[i];
            const uint8_t      I    = Color::Conv::GrayScale<uint8_t>::From(x11.r,x11.g,x11.b);
            std::cerr << std::setw(24) << x11.name << " : I=" << (int)I << std::endl;
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
}
Y_UDONE()
