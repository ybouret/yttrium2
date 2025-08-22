
#include "y/ink/area.hpp"

namespace Yttrium
{
    namespace Ink
    {
        static inline
        size_t udiff(const unit_t &lo, const unit_t &hi) noexcept
        {
            if(lo>hi) CoerceSwap(lo,hi);
            return (size_t)(1+hi-lo);
        }

        Area:: Area(const Coord lo, const Coord up) noexcept :
        lower(lo),
        upper(up),
        width( udiff(lower.x,upper.x), udiff(lower.y,upper.y) ),
        items(width.x*width.y)
        {
            assert(lower.x<=upper.x);
            assert(lower.y<=upper.y);
        }


        Area:: Area(const Area &area) noexcept  :
        lower(area.lower),
        upper(area.upper),
        width(area.width),
        items(area.items)
        {
        }

        Area & Area:: operator=( const Area & area ) noexcept
        {
            Coerce(lower) = area.lower;
            Coerce(upper) = area.upper;
            Coerce(width) = area.width;
            Coerce(items) = area.items;
            return *this;
        }

        Area:: ~Area() noexcept
        {
            
        }

    }

}

