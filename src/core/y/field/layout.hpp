//! \file

#ifndef Y_Field_Layout_Included
#define Y_Field_Layout_Included 1

#include "y/field/layout/metrics.hpp"
#include "y/field/layout/scope.hpp"
#include "y/object/counted.hpp"
#include "y/mkl/leap.hpp"

namespace Yttrium
{

    namespace Field
    {
        //______________________________________________________________________
        //
        //
        //
        //! Generic Layout
        //
        //
        //______________________________________________________________________
        template <typename COORD,typename COUNT>
        class Layout :
        public CountedObject,
        public LayoutScope<COUNT>,
        public LayoutMetrics,
        public Leap<COORD>
        {
        public:
            //__________________________________________________________________
            //
            //
            // Definition
            //
            //__________________________________________________________________
            static const unsigned DIMENSIONS = sizeof(COORD)/sizeof(unit_t); //!< space dimension
            typedef COORD       CoordType;                                   //!< alias
            typedef Leap<COORD> LeapType;                                    //!< alias
            using LayoutScope<COUNT>::width;
            using LayoutScope<COUNT>::shift;
            using LayoutScope<COUNT>::lastShift;

            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________

            //! cleanup
            inline virtual ~Layout() noexcept
            {

            }
            

            //! setup \param lo lower coordinates \param up upper coordinates
            inline explicit Layout(COORD lo, COORD up) noexcept :
            LayoutScope<COUNT>(),
            LayoutMetrics(DIMENSIONS, C2U(lo), C2U(up), C2S(width), C2S(shift)),
            LeapType(lo,up)
            {
            }
            

            //! setup as a sub-layout \param _ helper \param super super
            template <typename SUPER> inline
            explicit Layout(const SubLayout_ &_, const SUPER &super) noexcept :
            LayoutScope<COUNT>(_,super),
            LayoutMetrics(DIMENSIONS, lastShift() ),
            LeapType(Memory::Stealth::Conv<const COORD,const typename SUPER::CoordType>(super.lower),
                     Memory::Stealth::Conv<const COORD,const typename SUPER::CoordType>(super.upper) )
            {

            }



            //! display metrics
            inline friend std::ostream & operator<<(std::ostream &os, const Layout &l)
            {
                os << "#{[" << l.lower << "->" << l.upper << "]:" << l.width << "}=" << l.items << " (shift=" << l.shift <<")";
                return os;
            }



        private:
            Y_Disable_Copy_And_Assign(Layout); //!< discarding

            //! \param coord coordinate \return address of first component
            static inline unit_t * C2U(const COORD &coord) noexcept
            {
                return Memory::Stealth::Cast<unit_t>( &Coerce(coord) );
            }

            //! \param count coordinate \return address of first component
            static inline size_t * C2S(const COUNT &count) noexcept
            {
                return Memory::Stealth::Cast<size_t>( &Coerce(count) );
            }

        };
    }

}

#endif // !Y_Field_Layout_Included

