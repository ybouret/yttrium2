
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
        Leap<Coord>(lo,up),
        width( udiff(lower.x,upper.x), udiff(lower.y,upper.y) ),
        items(width.x*width.y)
        {
            assert(lower.x<=upper.x);
            assert(lower.y<=upper.y);
        }


        Area:: Area(const Area &area) noexcept  :
        Leap<Coord>(area),
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

        bool Area:: containsAbscissa(const unit_t x) const noexcept
        {
            return x>=lower.x && x<=upper.x;
        }

        bool Area:: containsOrdinate(const unit_t y) const noexcept
        {
            return y>=lower.y && y<=upper.y;
        }

        bool Area:: contains(const Coord p) const noexcept
        {
            return containsAbscissa(p.x) && containsOrdinate(p.y);
        }

        bool Area:: contains(const Area &a) const noexcept
        {
            return contains(a.lower) && contains(a.upper);
        }
        
    }

}

