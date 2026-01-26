//! \file

#ifndef Y_Ink_Area_Included
#define Y_Ink_Area_Included 1

#include "y/mkl/leap.hpp"
#include "y/mkl/v2d.hpp"

namespace Yttrium
{
    namespace Ink
    {
        typedef V2D<unit_t> Coord; //!< alias
        typedef V2D<size_t> Range; //!< alias


        //______________________________________________________________________
        //
        //
        //
        //! Area
        //
        //
        //______________________________________________________________________
        class Area : public Leap<Coord>
        {
        public:
            //__________________________________________________________________
            //
            //
            // C++
            //
            //__________________________________________________________________
            explicit Area(const Coord, const Coord) noexcept; //!< setup
            Area(const Area &)                      noexcept; //!< duplicate
            Area & operator=(const Area &)          noexcept; //!< assign \return *this
            virtual ~Area()                         noexcept; //!< cleanup

            //__________________________________________________________________
            //
            //
            // Methods
            //
            //________________________________________________________________
            bool containsAbscissa(const unit_t) const noexcept; //!< \return true if abscissa in area
            bool containsOrdinate(const unit_t) const noexcept; //!< \return true if ordinate in area
            bool contains(const Coord)          const noexcept; //!< \return true if point in area
            bool contains(const Area &)         const noexcept; //!< \return true if sub-area in area

            
            //__________________________________________________________________
            //
            //
            // members
            //
            //__________________________________________________________________
            const Range  width; //!< width
            const size_t items; //!< items

        };
    }

}

#endif // !Y_Ink_Area_Included

