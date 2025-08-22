
#include "y/field/layout/metrics.hpp"
#include <iostream>

namespace Yttrium
{

    namespace Field
    {

        LayoutMetrics:: ~LayoutMetrics() noexcept
        {
            Y_Memory_VZero(Coerce(items));
            Y_Memory_VZero(Coerce(dimensions));
        }
        
        LayoutMetrics:: LayoutMetrics(const unsigned d,
                                      unit_t * const lower,
                                      unit_t * const upper,
                                      size_t * const width,
                                      size_t * const shift) noexcept :
        dimensions(d),
        items(1)
        {
            assert(0!=lower);
            assert(0!=upper);
            assert(0!=width);

            for(unsigned i=0;i<dimensions;++i)
            {
                unit_t &lo = lower[i];
                unit_t &up = upper[i];
                if(up<lo) Swap(up,lo);
                Coerce(items) *= (width[i] = (size_t) (1+up-lo) );
            }

            Coerce(shift[0]) = width[0];
            for(unsigned i=1;i<dimensions;++i)
            {
                Coerce(shift[i]) = width[i] * shift[i-1];
            }
        }


        LayoutMetrics:: LayoutMetrics(const LayoutMetrics &layout) noexcept :
        dimensions(layout.dimensions),
        items(layout.items)
        {
        }
        
        LayoutMetrics:: LayoutMetrics(const unsigned d,
                                      const size_t   n) noexcept :
        dimensions(d),
        items(n)
        {
            
        }

    }

}

