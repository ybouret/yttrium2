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

            static inline SignType Compare(const FilterElement &lhs, const FilterElement &rhs) noexcept
            {
                const unit_t l2 = lhs.p.norm2();
                const unit_t r2 = rhs.p.norm2();
                switch( Sign::Of(l2,r2) )
                {
                    case Negative: return Negative;
                    case Positive: return Positive;
                    case __Zero__: break;
                }

                switch( Sign::Of(lhs.p.y,rhs.p.y) )
                {
                    case Negative: return Negative;
                    case Positive: return Positive;
                    case __Zero__: break;
                }

                switch( Sign::Of(lhs.p.x,rhs.p.x) )
                {
                    case Negative: return Negative;
                    case Positive: return Positive;
                    case __Zero__: break;
                }


                return __Zero__;
            }

            const Point p;
            const T     w;



        private:
            Y_Disable_Copy_And_Assign(FilterElement);
        };


    }

}

#endif // !Y_Ink_Filter_Element_Included
