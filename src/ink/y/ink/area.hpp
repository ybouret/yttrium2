#ifndef Y_Ink_Area_Included
#define Y_Ink_Area_Included 1

#include "y/mkl/v2d.hpp"

namespace Yttrium
{
    namespace Ink
    {
        typedef V2D<unit_t> Coord;
        typedef V2D<size_t> Range;

        class Area
        {
        public:

            explicit Area(const Coord, const Coord) noexcept;
            Area(const Area &)                      noexcept;
            Area & operator=(const Area &)          noexcept;
            virtual ~Area()                         noexcept;

            const Coord  lower;
            const Coord  upper;
            const Range  width;
            const size_t items;

        };
    }

}

#endif

