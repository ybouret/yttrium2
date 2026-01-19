
#include "y/ink/histogram.hpp"
#include "y/utest/run.hpp"
#include "y/concurrent/api/simd/crew.hpp"
#include "y/concurrent/api/simd/sole.hpp"
#include "y/random/park-miller.hpp"

using namespace Yttrium;

namespace Yttrium
{
    static inline uint8_t ByteToByte(const uint8_t u) noexcept
    {
        return u;
    }
}

Y_UTEST(hist)
{
    Random::ParkMiller    ran;
    Concurrent::Processor cpus = new Concurrent::Crew( Concurrent::Site::Default );
    Concurrent::Processor cpu1 = new Concurrent::Sole();
    Ink::Broker           par(cpus);
    Ink::Broker           seq(cpu1);
    Ink::Pixmap<uint8_t>  pxm8(100,200);
    for(size_t j=0;j<pxm8.h;++j)
    {
        for(size_t i=0;i<pxm8.w;++j)
        {
            
        }
    }
    Ink::Histogram Hseq, Hpar;

    Hseq.add(seq,pxm8,ByteToByte);





}
Y_UDONE()

