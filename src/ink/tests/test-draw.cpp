
#include "y/ink/draw/circle.hpp"
#include "y/ink/draw/line.hpp"
#include "y/ink/image/formats.hpp"
#include "y/utest/run.hpp"
#include "y/color/x11.hpp"
#include "y/random/park-miller.hpp"

using namespace Yttrium;
using namespace Ink;

namespace
{
    static inline void putWhite(const unit_t x, const unit_t y, Image &img)
    {
        assert(img.contains( Point(x,y) ));
        img[y][x] = Y_White;
    }

    static inline void putColor(const unit_t x, const unit_t y, Image &img, Random::Bits &ran)
    {
        assert(img.contains( Point(x,y) ));
        const RGBA c( ran.to<uint8_t>(), ran.to<uint8_t>(),ran.to<uint8_t>()) ;
        img[y][x] = c;
    }

}

Y_UTEST(draw)
{
    Random::ParkMiller ran;
    Formats &          IMG = Formats::Std();
    IMG.display(std::cerr,0);

    Image  img(256,128);

    for(size_t i=0;i<3;++i)
    {
        const unit_t x0 = ran.in<unit_t>(img.lower.x,img.upper.x);
        const unit_t x1 = ran.in<unit_t>(img.lower.x,img.upper.x);
        const unit_t y0 = ran.in<unit_t>(img.lower.y,img.upper.y);
        const unit_t y1 = ran.in<unit_t>(img.lower.y,img.upper.y);
        Draw::Line_(x0,y0,x1,y1,putWhite,img);
    }

    for(size_t i=0;i<3;++i)
    {
        const unit_t x0 = ran.in<unit_t>(img.lower.x,img.upper.x);
        const unit_t x1 = ran.in<unit_t>(img.lower.x,img.upper.x);
        const unit_t y0 = ran.in<unit_t>(img.lower.y,img.upper.y);
        const unit_t y1 = ran.in<unit_t>(img.lower.y,img.upper.y);
        Draw::Line_(x0,y0,x1,y1,putColor,img,ran);
    }

    for(size_t i=0;i<3;++i)
    {
        const unit_t xm = ran.in<unit_t>(img.lower.x,img.upper.x);
        const unit_t ym = ran.in<unit_t>(img.lower.y,img.upper.y);
        const unit_t r  = ran.in<unit_t>(0,img.upper.x/3);
        Draw::Circle(img,xm,ym,r,putWhite);
    }

    for(size_t i=0;i<3;++i)
    {
        const unit_t xm = ran.in<unit_t>(img.lower.x,img.upper.x);
        const unit_t ym = ran.in<unit_t>(img.lower.y,img.upper.y);
        const unit_t r  = ran.in<unit_t>(0,img.upper.x/3);
        Draw::Circle(img,xm,ym,r,putColor,ran);
    }

    IMG.save(img, "draw.png", 0);

}
Y_UDONE()

