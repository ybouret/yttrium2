
#include "y/ink/histogram.hpp"
#include "y/utest/run.hpp"
#include "y/concurrent/api/simd/crew.hpp"
#include "y/concurrent/api/simd/sole.hpp"
#include "y/random/park-miller.hpp"
#include "y/color/gray.hpp"

using namespace Yttrium;

namespace Yttrium
{
    static inline uint8_t ByteToByte(const uint8_t u) noexcept
    {
        return u;
    }

    static inline uint8_t FloatToByte(const float f) noexcept
    {
        return Color::Gray::UnitToByte(f);
    }


}

Y_UTEST(hist)
{
    Random::ParkMiller    ran;
    Concurrent::Processor cpus = new Concurrent::Crew( Concurrent::Site::Default );
    Concurrent::Processor cpu1 = new Concurrent::Sole();
    Ink::Broker           par(cpus);
    Ink::Broker           seq(cpu1);
    Ink::Histogram Hseq, Hpar;

    {
        Ink::Pixmap<uint8_t>  pxm8(100,200);
        for(size_t j=0;j<pxm8.h;++j)
        {
            for(size_t i=0;i<pxm8.w;++i)
            {
                pxm8(j)(i) = ran.to<uint8_t>();
            }
        }

        Hseq.add(seq,pxm8,ByteToByte);
        Hpar.add(par,pxm8,ByteToByte);

        Y_ASSERT(Hseq==Hpar);
    }

    Hseq.ldz();
    Hpar.ldz();
    {
        Ink::Pixmap<float>  pxm(10,20);
        for(size_t j=0;j<pxm.h;++j)
        {
            for(size_t i=0;i<pxm.w;++i)
            {
                pxm(j)(i) = ran.to<float>();
            }
        }

        Hseq.add(seq,pxm,FloatToByte);
        Hpar.add(par,pxm,FloatToByte);

        Y_ASSERT(Hseq==Hpar);
    }


}
Y_UDONE()

