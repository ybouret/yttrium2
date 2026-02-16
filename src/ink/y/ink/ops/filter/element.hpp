//! \file

#ifndef Y_Ink_Filter_Element_Included
#define Y_Ink_Filter_Element_Included 1

#include "y/ink/area.hpp"

namespace Yttrium
{
    namespace Ink
    {
        template <typename T> class FilterElement
        {
        public:
            inline  FilterElement(const Point _p, const T _w) : p(_p),  w(_w) {}
            inline ~FilterElement() noexcept {}

            inline friend std::ostream & operator<<(std::ostream &os, const FilterElement &self)
            {
                os << '@' << self.p << "=" << self.w;
                return os;
            }

            const Point p;
            const T     w;



        private:
            Y_Disable_Copy_And_Assign(FilterElement);
        };


    }

}

#endif // !Y_Ink_Filter_Element_Included
