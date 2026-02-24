//! \file

#ifndef Y_Ink_Filter_Element_Included
#define Y_Ink_Filter_Element_Included 1

#include "y/ink/area.hpp"

namespace Yttrium
{
    namespace Ink
    {

        //______________________________________________________________________
        //
        //
        //
        //! weight+position for filter/blur
        //
        //
        //______________________________________________________________________
        template <typename T> class FilterElement
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! setup \param _p point \param _w weight
            inline  FilterElement(const Point _p, const T _w) : p(_p),  w(_w) {}

            //! cleanup
            inline ~FilterElement() noexcept {}

            //! display
            inline friend std::ostream & operator<<(std::ostream &os, const FilterElement &self)
            {
                os << '@' << self.p << "=" << self.w;
                return os;
            }

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //__________________________________________________________________

            //! \param lhs lhs \param rhs rhs \return compare by increasing radius then position
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

            //__________________________________________________________________
            //
            //
            // Members
            //
            //__________________________________________________________________
            const Point p; //!< position
            const T     w; //!< weight



        private:
            Y_Disable_Copy_And_Assign(FilterElement); //!< discarding
        };


    }

}

#endif // !Y_Ink_Filter_Element_Included
