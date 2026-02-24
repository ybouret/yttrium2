#include "y/ink/blur/metrics.hpp"
#include "y/calculus/iabs.hpp"

namespace Yttrium
{
    namespace Ink
    {
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

    }

}

