

#include "y/ink/image/format/bmp.hpp"

#include "y/color/rgba.hpp"
#include "y/utest/run.hpp"
#include "y/concurrent/api/simd/crew.hpp"
#include "y/concurrent/api/simd/sole.hpp"
#include "y/color/gray.hpp"

using namespace Yttrium;

namespace Yttrium
{
    namespace Ink
    {

        static inline
        Pixmap<RGBA> GetSurface()
        {
            return Pixmap<RGBA>(10,7);
        }
    }
}

Y_UTEST(io)
{
#if 0
    Concurrent::Processor cpus = new Concurrent::Crew( Concurrent::Site::Default );
    Concurrent::Processor cpu1 = new Concurrent::Sole();
    Ink::Broker           par(cpus);
    Ink::Broker           seq(cpu1);
#endif

    Ink::FormatBMP  bmp;
    bmp.renderExtension();
    
}
Y_UDONE()

